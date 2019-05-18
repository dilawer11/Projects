Strong DC Chord

How to run:

For First Node :

$ python chord.py [portNo]

For Additional nodes

$ python chord.py [portNo] [existedPortNo]

portNo means the port you want this node to run on e.g 8000, 9000

existingPortNo means the port of any node already in the DHT chord

Example:

1st Node:

$ python chord.py 8000

2nd Node:

$ python chord.py 9000 8000

3rd Node :

$ python chord.py 10000 8000


