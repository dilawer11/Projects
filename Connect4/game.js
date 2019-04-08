new Vue({
    template:`

    <div style="text-align:center">
        <br><br>
        <h2>Welcome To Game</h2>
        <p> Message : {{msg}}<p>
        <br><br>
        <div v-if="!gameStarted">
            <button @click="initGrid()">Start Game</button>
        </div>
        <div v-if="gameStarted" @mousemove="updateCoordinates" @click="clickHandler" >
            <div v-for="(line,index) in grid" :key="index">
                <div :id="item.id" style="border: 5px solid gray; width:20px;display: inline-block" v-for="item in line" :key="item.id">{{item.display}}</div>
            </div>
        </div
        
    </div>

    `,

    data:{
        grid:[],
        gameStarted:false,
        cor :{
            x:0,
            y:0
        },
        msg:'Your turn',
        mark:'X',
        turn:true,
        ws: new WebSocket('ws://localhost:8080'),
    },
    methods:{
        initGrid(){
            for(let i =0;i<6;i++){
                this.grid.push([])
                for(let j=0;j<7;j++){
                    this.grid[i].push({display:'0' ,id: (7*i)+j});
                }
            }
            this.gameStarted=true;
        },
        updateCoordinates(e){
            this.cor.x = e.offsetX;
            this.cor.y = e.offsetY;
        
        },
        clickHandler(e){
            clickC = e.target.id % 7;
            updated=false
            if(!this.turn) {
                return;
            }
            for(let i=5 ;i>=0;i-=1){
                if(this.grid[i][clickC].display=='0'){
                    
                    updated=true;
                    this.ws.send(JSON.stringify({
                        type:'move',
                        col:clickC,
                        row: i,
                        mark:this.mark
                    }));
                    this.turn=false;
                    this.msg='Opponent turn';
                    break;
                }
            }
            if(updated==false){
                this.msg='Please choose Another col';
            }

            

        }
    },
    mounted(){
        this.ws.onmessage= payload=>{
            message=JSON.parse(payload.data);
            if(message.type=='moveStatus'){
                if(message.status=='confirmed'){
                    this.grid[message.row][message.col].display=this.mark;
                    console.log('Here')
                    this.turn=true;
                }
            }
        }
    },
    computed:{

    }

}).$mount('#app')