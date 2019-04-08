const http = require('http');
const ws= require('ws');
const fs = require('fs');

const readFile = file => new Promise((resolve, reject) => fs.readFile(file, (err, data) => err?reject(err):resolve(data)))

const initGrid = ()=>{
    grid=[];
    for(let i =0;i<6;i++){
        grid.push([])
        for(let j=0;j<7;j++){
            grid[i].push({display:'0' ,id: (7*i)+j});
        }
    }    return grid;
}
const server = http.createServer(async (request,response)=>{
    response.end(await readFile(__dirname+(request.url=='/game.js'?'/game.js':'/index.html')))
}).listen(8080);
console.log('Server Starting...')


const wss = new ws.Server({server});

wss.on('connection',client=>{
    console.log("Connection Request");
    grids=initGrid();
    client.on('message', async payload=>{
        data=JSON.parse(payload)
        console.log(data.type);
        console.log(data.col,data.row)
        grids[data.row][data.col].display=data.mark;
        client.send(JSON.stringify({
            type:'moveStatus',
            status: 'confirmed',
            col:data.col,
            row:data.row
        }))
        console.log(grids);
    })
})
