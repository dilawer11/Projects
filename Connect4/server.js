const http = require('http')
const WebSocket = require('ws')
const fs = require('fs')

const readFile = file => new Promise((resolve, reject) => fs.readFile(file, (err, data) => err?reject(err):resolve(data)))

games={0:[]}
game_number=0
game_states={}
watchers_states={}
client_States={}


const server = http.createServer(async (request, response) =>{
    response.end(await readFile(__dirname + (request.url=='/client.js'?'/client.js':'/index.html')))
} ).listen(8000)

const makemove=(move,data,color)=>{
	console.log("make move")
	for(i =  data[move].length ; i != 0; i--){
        if(data[move][i-1] == "grey"){
			data[move].splice(i-1, 1, color)
			console.log("data:  ",data)
            return true
        }
    }
    return false
}

const win_check=(color,array)=>{
	for(i=0;i<7;i++)
	{
		for(j=0;j<4;j++)
			{
				if(array[i][j]==color && array[i][j+1]==color && array[i][j+2]==color && array[i][j+3]==color)
				{
					return true
				}
				else
				{
					continue
				}
			}
	}

	for(i=0;i<3;i++)
	{
		for(j=0;j<7;j++)
			{
				if(array[i][j]==color && array[i+1][j]==color && array[i+2][j]==color && array[i+3][j]==color)
				{
					return true
				}
				else
				{
					continue
				}
			}
	}
	
	for(i=0;i<4;i++)
	{
		for(j=5;j>2;j--)
			{
				if(array[i][j]==color && array[i+1][j-1]==color && array[i+2][j-2]==color && array[i+3][j-3]==color)
				{
					return true
				}
				else
				{
					continue
				}
			}
	}

	for(i=0;i<4;i++)
	{
		for(j=0;j<3;j++)
			{
				if(array[i][j]==color && array[i+1][j+1]==color && array[i+2][j+2]==color && array[i+3][j+3]==color)
				{
					return true
				}
				else
				{
					continue
				}
			}
	}
}
console.log("Server Starting")
const game_start=(player)=>{

	games[game_number].push(player)
	console.log("A Player selected the play option")
	if(games[game_number].length==2)
	{
		console.log("pair found")
		p1=games[game_number][0]
		p2=games[game_number][1]
		watchers_states[game_number]=[]
		games[game_number+1]=[]
		data={
			id:game_number,
			player:0,
			win:0,
			turn:0,
			"matrix":[["grey","grey","grey","grey","grey","grey"]
			,["grey","grey","grey","grey","grey","grey"]
			,["grey","grey","grey","grey","grey","grey"]
			,["grey","grey","grey","grey","grey","grey"]
			,["grey","grey","grey","grey","grey","grey"]
			,["grey","grey","grey","grey","grey","grey"]
			,["grey","grey","grey","grey","grey","grey"]]
		}
		game_states[game_number]=data
		game_states[game_number].player=1
		game_states[game_number].turn=1
		p1.send(JSON.stringify(game_states[game_number]))
		game_states[game_number].player=2
		game_states[game_number].turn=0
		p2.send(JSON.stringify(game_states[game_number]))
        client_States[p1._socket.remoteAddress + ":" + p1._socket.remotePort] = {otherPlayer: p2, p1Turn: 1, p2Turn: 0, id: game_number, player: 1}
        client_States[p2._socket.remoteAddress + ":" + p2._socket.remotePort] = {otherPlayer: p1, p1Turn: 1, p2Turn: 0, id: game_number, player: 2}
        game_number++

	}
}

const wss = new WebSocket.Server({server})
wss.on('connection', client => {
	console.log("A connection is formed")
	client.on('message', async game => {

		   message=JSON.parse(game)

		   if(message.type=="menu"){

		   		if(message.input==1)
		   		{	
					console.log("yahan aa gaya mein")
		   			game_start(client)
		   		}
		   		else
		   		{
					console.log("keys sent")
		   			client.send(JSON.stringify(Object.keys(game_states)))
		   		}
		   }

		   else if(message.type=="watch")
		   {
			   console.log("watch me aa gaya")
		   		watchers_states[message.input].push(client)
		   		client.send(JSON.stringify(game_states[message.input]))
		   }

		   else if(message.type=="quit_watch")
		   {
		   		watchers_states[(message.input)[0]].splice((message.input)[1])
		   }

		   else if(message.type=="play")
		   {
			clientId = client._socket.remoteAddress + ":" + client._socket.remotePort
            id = client_States[clientId]["id"]
            p1 = client_States[clientId]["player"] == 1? client: client_States[clientId]["otherPlayer"]
            p2 = client_States[clientId]["player"] == 2? client: client_States[clientId]["otherPlayer"]
            color = client_States[clientId]["player"] == 1? "red": "black"
            p1Turn = client_States[clientId]["player"] == 1? 0: 1
            p2Turn = client_States[clientId]["player"] == 1? 1: 0
            turn = client_States[clientId]["player"] == 1? p2Turn: p1Turn
            clientId2 = client_States[clientId]["otherPlayer"]._socket.remoteAddress + ":" + client_States[clientId]["otherPlayer"]._socket.remotePort
            move = message["input"]
            if(move == -1){
                game_states[id]["win"] = color == "black"? 2: 1
                client_States[clientId]["otherPlayer"].send(JSON.stringify(game_states[id]))
                for(i = 0; i < watchers_states[id].length; i++){
                    watchers[id][i].send(JSON.stringify(game_states[id]))
                }
                delete game_states[id]
                delete client_States[clientId]
                delete client_States[clientId2]
                delete watchers_states[id]
                delete games[id]
            }
            else if(turn){
                makemove(move, game_states[id]["matrix"], color)
                client_States[clientId]["p1Turn"] = p1Turn
                client_States[clientId]["p2Turn"] = p2Turn
                client_States[clientId2]["p1Turn"] = p1Turn
                client_States[clientId2]["p2Turn"] = p2Turn
                if(win_check(color,game_states[id]["matrix"]))
                    game_states[id]["win"] = color == "red"? 1: 2
                game_states[id]["turn"] = p1Turn
                game_states[id]["player"] = 1
                p1.send(JSON.stringify(game_states[id]))
                game_states[id]["turn"] = p2Turn
                game_states[id]["player"] = 2
                p2.send(JSON.stringify(game_states[id]))
                for(i = 0; i < watchers_states[id].length; i++){
                    watchers_states[id][i].send(JSON.stringify(game_states[id]))
                }
                if(game_states[id]["win"] != 0){
                    delete game_states[id]
                    delete client_States[clientId]
                    delete client_States[clientId2]
                    delete watchers_states[id]
                    delete games[id]

                }


            }
		  	 }


		})
	})