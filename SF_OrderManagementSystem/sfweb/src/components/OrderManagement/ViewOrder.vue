<template>
    <div class="view-order">
        <div v-if="loading" class="progress">
            <div class="indeterminate"></div> 
        </div>
        <h2 class="center-align black-text">View Order</h2>
        
        <div class="container" v-if="order">
            <div class="row" style="padding:20px">
                <div class="col s12 m6 l6">
                    <h6 class="grey-text">Name: &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="black-text indent">{{order.name}}</span></h6>
                    <h6 class="grey-text">Email ID : <span class="black-text indent">{{order.email}}</span></h6>
                    <h6 class="grey-text">Phone: &nbsp;&nbsp;&nbsp;&nbsp;<span class="black-text indent">{{order.phone}}</span></h6>
                </div>
                <div class="col s12 m6 l6">
                    <h6 class="grey-text">Order No: <span class="black-text indent">{{order.no}}</span></h6>
                    <h6 class="grey-text">Status: &nbsp;&nbsp;&nbsp;&nbsp; <span class="black-text indent">{{order.status}}</span></h6>
                </div>
        
            </div>
            <div class="divider"></div>
            <div class="row">
          
                <div class="col s12 m12 l12">
                    <table class="responsive-table highlight">
                        <thead>
                            <tr>
                                <th>Item Name</th>
                                <th>Quantity</th>
                                <th>Size</th>
                                <th>Price</th>
                                <th>Total</th>
                            </tr>
                        </thead>
                        <tbody>
                            <tr v-for="(item,index) in order.items" :key="index" >
                                <td>{{item.name}}</td>
                                <td>{{item.quantity}}</td>
                                <td>{{item.size}}</td>
                                <td>{{item.price}}</td>
                                <td>{{item.total}}</td>
                            </tr>
                        </tbody>
                    </table>
                    <br>
                    <h6 class="right-align grey-text">Total Amount: <span class="indent black-text">{{totalAmount}} &nbsp;&nbsp;</span></h6>
                </div>
            </div>
            <div class="row status">
                <div class="input-feild col s6 m4">
                    
                    <select v-model="selectedStatus" @change="changeStatus" class="browser-default">
                        <option value="" disabled selected> Choose a status</option>
                        <option v-for="(item,i) in statusOptions" :key="i">{{item}}</option>
                    </select>
                    <label>Change Status</label> 
                </div>
                <div class="input-feild col s6 m4">
                    <router-link :to="{name:'EditOrder',params: {order_no: this.order.no}}">
                    <a class="waves-effect waves-light btn-large red darken-2">Edit Order</a>
                    </router-link>
                </div>
                 <div class="input-feild col s6 m4">
                    <span class="waves-effect waves-light btn-large red darken-2" @click="archiveOrder">Delete Order </span>
                </div>
            </div>
        </div>
    </div>
</template>

<script>
import db from '@/firebase/init'
import { mapState } from 'vuex'
export default {
    name: 'ViewOrder',
    data(){
        return{
            loading:true,
            feedback:true,
            order:null,
            selectedStatus:null,
        }
    },
    methods:{
        changeStatus(){
            if(this.selectedStatus!=this.order.status){
                this.loading=true;
                this.order.status=this.selectedStatus;
                db.collection('orders').doc(this.order.id).update(this.order).then(()=>{
                    this.loading=false;            
                }).catch(err=>{
                    alert('Something went wrong please try again later')
                    console.log(err)
                    this.loading=false;
                })
            }
        },
        archiveOrder(){
            if(confirm('ARE YOU SURE YOU WANT TO DELETE THIS ORDER')){
                this.selectedStatus="ARCHIVED"
                this.changeStatus()
                this.$router.push({name:'OrdersIndex'})
            }
        }
    },
    created(){
        this.loading=true;
        let ref = db.collection('orders').where('no', '==', this.$route.params.order_no)
        ref.get().then(snapshot =>{
            if(snapshot.empty){
                alert('Cannot find the order in the database')
                this.$router.push({name: 'OrdersIndex'})
            } else{
                snapshot.forEach(doc => {
                    this.order = doc.data()
                    this.order.id = doc.id;
                    this.selectedStatus=this.order.status
                })
            }   
            this.loading=false;
           }).catch(err=>{
            this.feedback= 'Database returned an error'
            console.log(err)
            this.loading=false;
        })
    },
    computed:{
        ...mapState(['statusOptions']),
        totalAmount: function (){
            return this.order.items.reduce((num,item)=>item.total+num,0)
        },
    }
}
</script>

<style>
.view-order .indent{
    padding-left:1.8em;
    padding-right:1.8em;
}
</style>
