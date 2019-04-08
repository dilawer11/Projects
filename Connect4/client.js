new Vue({
	template:
	`<div>	
			<div v-if="page==0">
			<div v-on:click="game_start(1)" @mouseover = "box_high1" @mouseleave = "box_low1" v-bind:style='{"border": "1px solid","margin": "10px 0px","padding":"20px 10px","color": box_text,"text-align":"center","background-color": this.box_color1}'>
			<p style="font-weight:bolder;">Start a new Game</p>
			</div><br>
			<div v-on:click="game_start(2)"	 @mouseover = "box_high2" @mouseleave = "box_low2" v-bind:style='{"border": "1px solid","margin": "10px 0px","padding":"15px 10px","color": box_text,"text-align":"center","background-color": this.box_color2}'>
			<p style="font-weight:bolder;">Watch a Game</p>	
			</div><br>
			</div>

			<div v-if="page==4 && watchMode==true">
				

					
					<div v-bind:style='{"border": "1px solid","margin": "10px 0px","padding":"15px 10px","color": box_text,"text-align":"center","background-color": this.box_color}'>
							
							  		You are in Watch mode
							  	
					</div><br>
					<div v-bind:style="centergame">
								<div v-for='(column,i) in color_array'>  
								<div v-bind:style="floating">
									<div>
										<div @mouseover="hover_over(i)" @mouseleave="hover_leave(i)" v-for="color in column">
											<div  v-bind:style='{height:"35px",width:"35px","background-color":square_color[i]}'>
											<div v-bind:style='{height:"35px",width:"35px","background-color":color,"border-radius": "50%"}'></div>			
											</div>
										</div>
									</div>
								</div>
						
					</div><br><br><br><br><br><br><br><br><br><br><br><br><br>
			
			
			<div v-on:click="quit()" @mouseover = "box_high2" @mouseleave = "box_low2" v-bind:style='{"border": "1px solid","margin": "10px 0px","padding":"15px 10px","color": box_text,"text-align":"center","background-color": this.box_color2}'>
			<p style="font-weight:bolder;">Quit</p>	
			</div><br>
			</div>
			
			</div>
			
		





			<div v-if="page==1 && watchMode==false">
					<div  v-if="turn==undefined" v-bind:style='{"border": "1px solid","margin": "10px 0px","padding":"15px 10px","color": box_text,"text-align":"center","background-color": this.box_color2}'>
					  <div v-on:click="waiting">
					  		
							  	<div>
							  		{{user_message}}
							  	</div>
						  	
					  </div>
					</div>

					<div v-else >
					<div v-bind:style='{"border": "1px solid","margin": "10px 0px","padding":"15px 10px","color": box_text,"text-align":"center","background-color": this.box_color}'>
							
							  		{{user_message}}
							  	
					</div><br>
					<div v-bind:style="centergame">
								<div v-on:click="Move(i)" v-for='(column,i) in color_array'>  
								<div v-bind:style="floating">
									<div>
										<div @mouseover="hover_over(i)" @mouseleave="hover_leave(i)" v-for="color in column">
											<div  v-bind:style='{height:"35px",width:"35px","background-color":square_color[i]}'>
											<div v-bind:style='{height:"35px",width:"35px","background-color":color,"border-radius": "50%"}'></div>			
											</div>
										</div>
									</div>
								</div>
						s	</div>
					</div><br><br><br><br><br><br><br><br><br><br><br><br><br>
			
			
			<div v-on:click="quit()" @mouseover = "box_high2" @mouseleave = "box_low2" v-bind:style='{"border": "1px solid","margin": "10px 0px","padding":"15px 10px","color": box_text,"text-align":"center","background-color": this.box_color2}'>
			<p style="font-weight:bolder;">Quit</p>	
			</div><br>
			</div>
			
			</div>
			
			<div v-else-if="page==2">

				<div v-for="(o,i) in watch">
				<div v-on:click = "gameSelect(o)" v-on:mouseover = "o.splice(1, 1, 'lightblue')" v-on:mouseleave = "o.splice(1, 1, 'pink')" v-bind:style='{"border": "1px solid","margin": "10px 0px","padding":"20px 10px","color": box_text,"text-align":"center","background-color": o[1]}'>
				<p style="font-weight:bolder;">(Game in progress) ID : {{o[0]}}</p>
				</div><br>
				</div>
				<div v-on:click="quit()" @mouseover = "box_high2" @mouseleave = "box_low2" v-bind:style='{"border": "1px solid","margin": "10px 0px","padding":"15px 10px","color": box_text,"text-align":"center","background-color": this.box_color2}'>
					<p style="font-weight:bolder;">Quit</p>	
					</div><br>
			</div>
		</div>`,

	data:{
		page:0,
		player:0,
		data:{},
		watchMode:false,
		turn:undefined,
		box_color2:"pink",
		user_message:"waiting for other Player",
		square_color:["lightblue","lightblue","lightblue","lightblue","lightblue","lightblue","lightblue"],
		danger:["green","green","green","green","green","green","green"],
		color_array:[],
		box_color1:"pink",
		box_color:"pink",
		watching:-1,
		box_text:"red",
		floating:{
			'float': 'left' 
		},
		watch:[],
		centergame:{
			'margin':'auto',
			width: '18.5%'
		},
		ws: new WebSocket('ws://localhost:8000'),
	},
	methods:
	{
		hover_over(i){
			color=this.player==2?"red":"black"
			console.log("Test",this.color_array)
			decision=this.makeMove(i,color,this.color_array)
			console.log("Decision", decision)
			if(decision)
			{
				console.log("decision 123131414")
				this.square_color.splice(i,1,"pink")
			}
			else{
				this.square_color.splice(i,1,"yellow")
			}
		},
		hover_leave(i){
			this.square_color.splice(i,1,"lightblue")
		},
		gameSelect(o) {
            this.watchMode = true
            this.ws.send(JSON.stringify({type:"watch",input:o[0]}))
            this.watching = o[0]
            this.page = 4
        },
		reset(){
            this.watch = []
            this.colColors = ["lightblue","lightblue","lightblue","lightblue","lightblue","lightblue","lightblue"]
            this.gameMatrix = [["lightgrey","lightgrey","lightgrey","lightgrey","lightgrey","lightgrey"],
                      ["lightgrey","lightgrey","lightgrey","lightgrey","lightgrey","lightgrey"],
                      ["lightgrey","lightgrey","lightgrey","lightgrey","lightgrey","lightgrey"],
                      ["lightgrey","lightgrey","lightgrey","lightgrey","lightgrey","lightgrey"],
                      ["lightgrey","lightgrey","lightgrey","lightgrey","lightgrey","lightgrey"],
                      ["lightgrey","lightgrey","lightgrey","lightgrey","lightgrey","lightgrey"],
                      ["lightgrey","lightgrey","lightgrey","lightgrey","lightgrey","lightgrey"],]
            this.watchMode = false
            this.watching = -1
            this.page = 0
            this.player = 0
            this.turn =  0
            this.data = {}
            this.message = 'Waiting...'
            console.log("done")
        },	
		box_high1()
		{
			this.box_color1="lightblue"
		},

		waiting(){
			this.user_message="Still waiting for the other player"
		},
		
		box_low1()
		{
			this.box_color1="pink"
		},
		
		box_high2()
		{
			this.box_color2="lightblue"
		},
		
		box_low2()
		{
			this.box_color2="pink"
		},

		game_start(i)
		{
			if(i==1)
			{
				console.log("play selected")
				this.page=1
				this.ws.send(JSON.stringify({
					type:"menu",
					input:1
				}))
			}
			else
			{
				console.log("watch selected")
				this.page=2
				console.log(this.page, " current page number")
				this.ws.send(JSON.stringify({
					type:"menu",
					input:2
				}))
			}
		},
		win_check(color,array){
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
		},
		cancelMove(move, color) {
            for(i = 0 ; i < this.color_array[move].length; i++){
                if(this.color_array[move][i] == color){
                    this.color_array[move].splice(i, 1, "grey")
                    return true
                }
            }
            return false
        },
        makeMove(move, color,copy_array) {
			array=copy_array
			console.log("test",array)
            for(i =  array[move].length ; i != 0; i--){
                if(array[move][i-1] == "grey"){
					array[move].splice(i-1, 1, color)
					hope=this.win_check(color,array)
					console.log("Win_check",hope)
					this.cancelMove(move,color)
                    return hope
				}
				console.log("yadadad")
			}
			return false
		},
		quit(){
            if(this.watchMode == true){
                this.watchMode = false                
                this.ws.send(JSON.stringify({"type":"quitWatch","input":[this.watching, this.player - 2]}))
                this.reset()
            }
            else{
                this.ws.send(JSON.stringify({"type":"play","input":-1}))
                this.reset()
            }
        },
		Move(c)
		{
			console.log("column: ",c)
			if(this.turn!=1)
			{
				this.user_message="Not your Turn"
			}
			else
			{
				this.ws.send(JSON.stringify({
					type:"play",
					input:c
				}))
			}

		}
		
	}

	,
	mounted(){
		this.ws.onmessage = message => {
			if(this.page==4)
			{
				message=JSON.parse(message.data)
				console.log("data from server: ",message)
				this.data=message
				console.log(message["matrix"])
                this.color_array = message["matrix"]
			}
			
			if(this.page==1)
			{
				message=JSON.parse(message.data)
				console.log("data from server: ",message)
				this.data=message
				console.log(message["matrix"])
                this.color_array = message["matrix"]
                this.player = this.data["player"]
                this.turn = this.data["turn"]
				console.log("color scheme: ", this.color_array)
				if(this.player==message.win)
				{
					this.user_message="Game over...You won :))"
					setTimeout(() => this.reset(), 5000);
				}

				else if(message.win==0)
				{
					console.log("Second place")
					if(this.turn)
						this.user_message="Your turn"
					else
						this.user_message="Opponent turn"
				}
				else
				{
					this.user_message="Game over.....You lose :((("
					setTimeout(() => this.reset(), 5000);
				}
			}
			else if(this.page==2)
			{
				message=JSON.parse(message.data)
				console.log("Games in progress: ", message)
				for(i=0;i<message.length;i++)
				{
					this.watch.push([message[i],"pink"])
				}
				console.log("after pushing: ",this.watch)
			}
		}	
	}    
}).$mount('#app')