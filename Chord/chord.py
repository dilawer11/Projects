import socket
import os
import sys
import thread
import threading
import hashlib
import time



class fingerTableEntry:
	key = -1
	portNo = -1
	IPadd = '-1'
	value = -1


	def __init__(self,pKey,pPortNo,pIPadd):
		key=pKey
		portNo=pPortNo
		IPadd=pIPadd

	def __init__(self):
		key = -1
		portNo = '-1'
		IPadd = -1

class chord:
	predKey=0;
	predPort=0;
	fingerTable = []
	nextNodeP=0
	nextNodeK=0
	lastNewJoin = 0
	suc_suc = 0
	suc_suc_key =0
	port = 0
	ip = '127.0.0.1'
	key = 0
	consequence = True
	m = 64
	count = 0
	suc_unsure = False
	lastLeft = 0

	def __init__(self, own_port, other_port = None):
		if other_port is None:
			
			self.port = own_port
			self.key = self.hashery(own_port)
			self.predKey=self.key
			self.predPort=self.port
		

			## Creates finger table for your own self
			
			for i in range (0,6):
				self.fingerTable.append(fingerTableEntry())
				self.fingerTable[i].key=self.key
				self.fingerTable[i].portNo=int(self.port)
				self.fingerTable[i].IPadd=self.ip
				self.fingerTable[i].value=((self.key+(2**i))%self.m)
				

			s = socket.socket() 
			s.bind((self.ip, int(self.port)))

			t1 = threading.Thread(target = self.listener,args = (s,))
			t2 = threading.Thread(target = self.options,args= ())
			t3 = threading.Thread(target = self.check_Successor, args = ())

			t1.start()
			t2.start()
			t3.start()

		else:
			self.port = own_port
			self.key = self.hashery(own_port)

			s = socket.socket() 
			s.bind((self.ip, int(self.port)))
			self.connectToChord(other_port)
			self.createFingerTable(int(other_port))
			#self.join(other_port,s)
			self.fileGet()

			s = socket.socket()
			s.bind((self.ip, int(self.port))) 		

			t1 = threading.Thread(target = self.listener,args = (s,))
			t2 = threading.Thread(target = self.options,args= ())
			t3 = threading.Thread(target = self.check_Successor, args = ())

			t1.start()
			t2.start()
			t3.start()


	def fileGet(self):
		s = socket.socket()
		s.connect((self.ip, self.fingerTable[0].portNo))
		s.send('fileGet '+str(self.key))
		numOfFiles = int(s.recv(1024))
		s.send('ack')
		
		while(numOfFiles):
			fise = s.recv(1024)
			flist = fise.split(' ')
			filename = flist[0]
			size = int(flist[1])
			file = os.path.join(str(self.port), filename)
			s.send('ack')
			string = s.recv(1024)

			if(not os.path.exists(self.port)):
				os.makedirs(self.port)

			with open(file,'w+') as f:
				total_recieved = len(string)
				f.write(string)
				while total_recieved < size:
					string = s.recv(1024)
					total_recieved += len(string)
					f.write(string)

			numOfFiles -= 1
			

	
	def fileSend(self,peer,data):
		if(os.path.exists(self.port)):
			k = int(data[1])
			listOfFiles = os.listdir(self.port)
			toSend = filter((lambda x :self.hashery(x) <= k), listOfFiles)
			peer.send(str(len(toSend)))
			ack = peer.recv(1024)

			for filename in toSend:
				file = os.path.join(str(self.port), filename)
				peer.send(filename + ' '+ str(os.path.getsize(file)))
				ack = peer.recv(1024)

				with open(file, 'rb') as f:
					string = f.read(1024)
					peer.send(string)
					while string != '':
						string = f.read(1024)
						peer.send(string)

				
				time.sleep(0.1)

		else:
			peer.send('0')


	def connectToChord(self,otherPort):
		z = socket.socket()
		z.connect((self.ip,int(otherPort)))
		z.send('findSuccessor ' + str(self.key))
		ans = z.recv(1024)
		ansSplit= ans.split(' ')
		self.nextNodeP=int(ansSplit[0])
		self.nextNodeK=int(ansSplit[1])
		z.send('end')
		t = socket.socket()
		t.connect((self.ip,self.nextNodeP))
		t.send('getPredInfo')
		ans = t.recv(1024)
		nextPred=ans.split(' ')
		self.predKey=int(nextPred[1])
		self.predPort=int(nextPred[0])
		t.send('updatePred ' + str(self.port)+ ' '+str(self.key))
		dump=t.recv(1024)
		t.send('end')
		s = socket.socket()
		s.connect((self.ip,self.nextNodeP))
		s.send('newJoin ' + str(self.key) +' '+ str(self.port))
		ans = s.recv(1024)
		s.send('end')
		print "connectToChord returned"


	def createFingerTable(self,otherPort):
		print "In Create Finger Table"
		totalEntries = 6 #change this to log of 64
		predictedEntries = []
		
		for i in range(0,6):
			predictedEntries.append((self.key+(2**i))%self.m)

		tmpfingerTable=fingerTableEntry()
		tmpfingerTable.key=self.nextNodeK
		tmpfingerTable.portNo=self.nextNodeP
		tmpfingerTable.IPadd=self.ip
		tmpfingerTable.value=int(predictedEntries[0])
		self.fingerTable.append(tmpfingerTable)
		for i in range(1,6):
			s = socket.socket()
			# print "Create Finger Table Value : " + str(i)
			s.connect((self.ip,self.nextNodeP))
			s.send('findSuccessor '+ str(predictedEntries[i]))
			temp=s.recv(1024)
			#convert temp to port and key then store in finger table
			tempSplit= temp.split(' ')
			tmpfingerTable=fingerTableEntry()
			tmpfingerTable.key=int(tempSplit[1])
			tmpfingerTable.portNo=int(tempSplit[0])
			tmpfingerTable.IPadd=self.ip
			tmpfingerTable.value=int(predictedEntries[i])
			self.fingerTable.append(tmpfingerTable)
			s.send('end')
		print "createFingerTable returned"
			



	def PUT(self):
		filename = raw_input('name of file: ')
		
		if os.path.isfile(filename):
			size = os.path.getsize(filename)
			file_key = self.hashery(filename)

			to_send = self.findSuccessor(str(file_key))

			print ""
			print to_send
			print ""

			user = to_send.split(' ')

			z = socket.socket()
			z.connect((self.ip, int(user[0])))
			z.send('store ' + filename + ' ' + str(size))
			aack = z.recv(1024)

			with open(filename, 'rb') as f:
				byteToSend = f.read(1024)
				z.send(byteToSend)
				while byteToSend != "":
					byteToSend = f.read(1024)
					z.send(byteToSend)

			z.send('end')

		else:
			print "either file doesnot exist or is not in current directory"


	def store(self, peer, line):
		linesplit = line.split(' ')
		filename = linesplit[1]
		size = long(linesplit[2])

		peer.send('ack')

		string = peer.recv(1024)

		#Current_Directory = os.getcwd()
		file =  os.path.join(self.port, filename)#self.port + "\\" + filename
		print ""
		print file
		print ""
		
		if(not os.path.exists(self.port)):
			os.makedirs(self.port)

		f = open(file, "w+")
		total_recieved = len(string)
		f.write(string)
		while total_recieved < size:
			string = peer.recv(1024)
			total_recieved += len(string)
			f.write(string)
		#print 'done'

	def GET(self):
		filename = raw_input('name of file: ')
		hash_of_file = self.hashery(filename)

		node_with_file = self.findSuccessor(str(hash_of_file))
		user = node_with_file.split(' ')

		z = socket.socket()
		z.connect((self.ip, int(user[0])))
		z.send('get '+ filename)
		reply = z.recv(1024)
		
		if(reply == 'file not found'):
			print '\n file doesnot exist \n'
		else:
			data = reply.split(' ')
			filename = data[0]
			size = long(data[1])

			z.send('ack')

			string = z.recv(1024)

			#Current_Directory = os.getcwd()
			file =  os.path.join(self.port, filename)#self.port + "\\" + filename
		
			if(not os.path.exists(self.port)):
				os.makedirs(self.port)

			f = open(file, "w+")
			total_recieved = len(string)
			f.write(string)
			while total_recieved < size:
				string = z.recv(1024)
				total_recieved += len(string)
				f.write(string)

		z.send('end')
		#print 'done'

	def upload(self,peer,filename):
		file = os.path.join(self.port, filename)
		if(os.path.exists(file)):
			size = os.path.getsize(file)

			peer.send(filename + ' ' + str(size))
			ack = peer.recv(1024)

			with open(file, 'rb') as f:
				byteToSend = f.read(1024)
				peer.send(byteToSend)
				while byteToSend != "":
					byteToSend = f.read(1024)
					peer.send(byteToSend)

		else:
			peer.send('file not found')


	def viewFiles(self):
		if(os.path.exists(self.port)):
			print os.listdir(self.port)
		else:
			print "No files stored yet"



	def options(self):
		while(self.consequence): # change this to global etc etc explained above
			
			print "Menu:"
			print "1. Store a File"
			print "2. Find a File"
			print "3. Files stored here"
			print "4. FingerTable details"
			print "5. logout"
			print "\n"

			choice = raw_input("=> ")
			if choice == '1':
				print 'store a file\n'
				self.PUT()
				print '\n file stored \n'
			elif choice == '2':
				print 'find a file\n'
				self.GET()
				print '\n file got and stored \n'
			elif choice == '3':
				print 'Files stored here\n'
				self.viewFiles()
			elif choice == '4':
				self.printFingerTable()

			elif choice == '5':
				print "logout\n"
				#self.consequence = False
				z = socket.socket()
				z.connect((self.ip, int(self.port)))
				z.send('logout')
				self.consequence = False
			else:
				print "invalid choice\n"
				
	def newJoinHandler(self,pKey,pPort):
		iKey=int(pKey)
		iPort=int(pPort)

		if (iKey==self.key or self.lastNewJoin==iKey):
			return
		else:
			self.lastNewJoin=iKey


			for entry in self.fingerTable: #If your finger table needs to be updated
				if (iKey>=entry.value and iKey<entry.key):
					entry.key=iKey
					entry.portNo=iPort
				elif (entry.key<entry.value and iKey<entry.key):
					entry.key=iKey
					entry.portNo=iPort	
				elif (entry.key<entry.value and iKey>=entry.value):
					entry.key=iKey
					entry.portNo=iPort
			
			self.printFingerTable()
			for entry in self.fingerTable:
				if entry.key!=iKey:
					s=socket.socket()
					s.connect((self.ip,entry.portNo))
					s.send('newJoin '+ pKey + ' ' + pPort)
					temp = s.recv(1024)
					s.send('end')
			#send request to all in your finger table that new joined

	def printFingerTable(self):
		print "-----------------------"
		print "My Key : " + str(self.key)
		print "Pred Info " + str(self.predKey) + ' ' +str(self.predPort)
		print "suc of suc "+ str(self.suc_suc_key) + ' '+str(self.suc_suc) 
		for entry in self.fingerTable:
			print str(entry.key) + ' ' + str(entry.portNo)+ ' ' + str(entry.value)
		print "-----------------------" 
	

	def listener(self,s):	
		s.listen(100)
	
		while(self.consequence): # change this to a variable when deal with offline part. this goes to false if a person goes offline
			peer,addr = s.accept()
			thread.start_new_thread(self.dealer,(peer,addr))


	def dealer(self,peer,addr):
		while(True):
			string = peer.recv(1024)
			string_in_list = string.split(' ')

			if(string == 'hello'):
				peer.send(str(self.fingerTable[0].portNo) + ' ' + str(self.fingerTable[0].key))

			elif(string_in_list[0] == 'I'):
				if(string_in_list[3] == 'predecessor'):
					self.predPort = int(string_in_list[4])
					self.predKey = int(string_in_list[5])
					peer.send('ack')
				
			elif (string_in_list[0]=='newJoin'):
				self.newJoinHandler(string_in_list[1],string_in_list[2])
				peer.send('done')

			elif(string == 'successor?'):
				peer.send(str(self.fingerTable[0].portNo) + ' ' + str(self.fingerTable[0].key))

			elif(string == 'logout'):
				print 'handle sending files off etc and logout'
				self.logout()

			elif(string_in_list[0] == 'store'):
				self.store(peer,string)

			elif(string_in_list[0] == 'get'):
				self.upload(peer,string_in_list[1])

			elif(string_in_list[0] == 'fileGet'):
				self.fileSend(peer,string_in_list)
			
			elif (string_in_list[0]=='findSuccessor'):
				ans=self.findSuccessor(string_in_list[1])
				peer.send(ans)
			
			elif(string == 'getPredInfo'):
				#print "Getting Predecessor Info"
				ans = str(self.predPort) + ' ' +str(self.predKey)
				peer.send(ans)

			elif(string_in_list[0] == 'your'):
				self.contactSuc(int(string_in_list[3],int(string_in_list[4])))
			
			elif(string_in_list[0] == 'updatePred'):
				#print "Getting Successor Info"
				self.predKey=int(string_in_list[2])
				self.predPort=int(string_in_list[1])
				peer.send('done')

			elif(string_in_list[0]=='nodeLeft'):
				ans = self.nodeLeft(int(string_in_list[1]),int(string_in_list[2]),int(string_in_list[3]))
				peer.send(ans)

			elif(string == 'end'):
				peer.close()
				break


	def contactSuc(self,suc_port,suc_key):
		s = socket.socket()
		s.connect((self.ip, suc_port))
		s.send('I am new predecessor '+str(self.port) +' '+str(self.key))
		ack = s.recv(1024)
		s.send('end')


	def hashery(self,to_hash):
		hashie = hashlib.sha1(to_hash)		

		hex = hashie.hexdigest()

		num = 0
		multiplier = 2**40

		for each in hex:
			if (each >= '0' and each <= '9'):
				num += multiplier * int(each)
				multiplier /= 2
			else:
				if(each == 'a'):
					num += multiplier * 10
					multiplier/=2

				elif(each == 'b'):
					num += multiplier * 11
					multiplier/=2

				elif(each == 'c'):
					num += multiplier * 12
					multiplier/=2
				elif(each == 'd'):
					num += multiplier * 13
					multiplier/=2
				elif(each == 'e'):
					num += multiplier * 14
					multiplier/=2
				elif(each == 'f'):
					num += multiplier * 15
					multiplier/=2
			#print each + " %d %d" %(num, multiplier)

		print "key: %d" %(num % self.m)
		return num % self.m


	def findSuccessor(self,t):
		print "findSuccessor of " + t
			#create an array of all available keys to 


		pKey = int(t)
		if (self.predKey<self.key and pKey>self.predKey and pKey<self.key):
			return str(self.port)+ ' ' +str(self.key)
		elif (self.predKey>self.key and (pKey<self.key or pKey>self.predKey)):
			return str(self.port)+ ' ' +str(self.key)
		availableKeys = []
		availableKeys.append(self.key)
		for entry in self.fingerTable:
			if entry.key not in availableKeys:
				availableKeys.append(entry.key)

		availableKeys.sort()
		
		for k in availableKeys:
			if k==pKey:
				return str(self.getPort(k))+ ' ' +str(k)

		if pKey>self.key:
			maxInRange = -1
			for k in availableKeys:
				if k>self.key and k<pKey and k!=self.lastNewJoin and k>maxInRange:
					maxInRange=k
			if maxInRange!=-1:
				s=socket.socket()
				s.connect((self.ip,self.getPort(maxInRange)))
				s.send('findSuccessor '+ str(pKey))
				returnVal = s.recv(1024)
				s.send('end')
				return returnVal

		else:
			lowest = self.m+1
			for k in availableKeys:
				if k!=self.key and k<lowest and k!=self.lastNewJoin and k<pKey:
					lowest=k

			if lowest!=(self.m+1):
				s=socket.socket()
				s.connect((self.ip,self.getPort(lowest)))
				s.send('findSuccessor '+ str(pKey))
				returnVal = s.recv(1024)
				s.send('end')
				return returnVal

		### Take a decision if program reached here request can't be forwarded
		for i in range(0,len(availableKeys)):
			if availableKeys[i]>pKey:
				return str(self.getPort(availableKeys[i]))+ ' '+ str(availableKeys[i])

		#return first value in available keys
		return str(self.getPort(availableKeys[0])) + ' ' +str(availableKeys[0])

	def getPort(self,pKey):
		for entry in self.fingerTable:
			if entry.key==pKey:
				return entry.portNo

		if pKey==self.key:
			return self.port

		else:
			print "Error in getPort"

	def check_Successor(self):
		while(self.consequence):
			time.sleep(2)
			try:
				z = socket.socket()
				z.connect((self.ip, int(self.fingerTable[0].portNo)))
				
				z.send('hello')
				ans = z.recv(1024)
				anssplit = ans.split(' ')

				self.suc_suc = int(anssplit[0])
				self.suc_suc_key = int(anssplit[1])
				z.send('end')
				
			except:
				if(self.count < 1):
					self.count += 1
					suc_unsure = True
				
				else:
					print 'successor needs to be updated as he is lost\n'
					
					self.nodeLeft(self.fingerTable[0].portNo, self.suc_suc, self.suc_suc_key)
					z = socket.socket()
					print self.suc_suc
					z.connect((self.ip,int(self.suc_suc)))
					z.send('I am new predecessor ' + self.port + ' ' + str(self.key))
					ack = z.recv(1024)
					z.send('end')

					self.count = 0
					suc_unsure = False
					# doesnot connect means successor has left
					# when have fingertable, can go to any of the entries to find new successor
	

	def nodeLeft(self,key,sucKey, sucHashKey):

		if key==self.lastLeft:
			return 'done'

		else:
			self.lastLeft=key
			for entry in self.fingerTable:
			#connect to node and forward the request
				if entry.portNo != key:
					s = socket.socket()
					s.connect((self.ip,entry.portNo))
					s.send('nodeLeft '+str(key) + ' '+str(sucKey)+ ' '+ str(sucHashKey))
					resp = s.recv(1024)
					s.send('end')

			if self.predPort != key:
				s = socket.socket()
				s.connect((self.ip,self.predPort))
				s.send('nodeLeft '+str(key)+ ' '+str(sucKey)+ ' '+ str(sucHashKey))
				resp = s.recv(1024)
				s.send('end')
		#update your own fingerTable

			for entry in self.fingerTable:
				if entry.portNo == key:
					entry.portNo=sucKey
					entry.key = sucHashKey
			return 'updated'

	def logout(self):
		if(os.path.exists(self.port)):
			if(self.suc_unsure == False):
				z = socket.socket()
				z.connect((self.ip, int(self.fingerTable[0].portNo)))
				
				file_list = os.listdir(self.port)

				print ""
				print file_list
				print ""

				for file in file_list:
					z.send('store '+ file + ' ' + str(os.path.getsize(file)))
					ack = z.recv(1024)

					filename = os.path.join(self.port, file)
					with open(filename, 'rb') as f:
						byteToSend = f.read(1024)
						z.send(byteToSend)
						while byteToSend != "":
							byteToSend = f.read(1024)
							z.send(byteToSend)
						time.sleep(0.5)

				z.send('end')
				time.sleep(0.5)
				z = socket.socket()
				z.connect((self.ip, self.predPort))
				z.send('your new successor '+str(self.fingerTable[0].portNo) + ' '+ str(self.fingerTable[0].key))
				ack = z.recv(1024)
				z.send('end')
				self.nodeLeft(self.port,self.fingerTable[0].portNo,self.fingerTable.key)
			
			else:
				time.sleep(6)
				z = socket.socket()
				z.connect((self.ip, int(self.fingerTable[0].portNo)))
				for file in os.listdir(self.port):
					z.send('store '+ file +' '+ str(os.path.getsize(file)))
					ack = z.recv(1024)

					filename = os.path.join(self.port, file)
					with open(filename, 'rb') as f:
						byteToSend = f.read(1024)
						z.send(byteToSend)
						while byteToSend != "":
							byteToSend = f.read(1024)
							z.send(byteToSend)
						time.sleep(0.5)

				z.send('end')
				time.sleep(0.5)
				z = socket.socket()
				z.connect((self.ip, self.predPort))
				z.send('your new successor '+str(self.fingerTable[0].portNo) + ' '+ str(self.fingerTable[0].key))
				ack = z.recv(1024)
				z.send('end')
				self.nodeLeft(self.port,self.fingerTable[0].portNo,self.fingerTable.key)
def Main():
	if(len(sys.argv) == 3): # additional node
		c = chord(sys.argv[1], sys.argv[2])

	elif(len(sys.argv) == 2): #first node
		c = chord(sys.argv[1])
	else:
		print 'Specify Atleast 1 and At Max Two Ports'

if __name__ == '__main__':
	Main()