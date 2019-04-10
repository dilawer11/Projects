<template>
    <div class="edit-order">
        <div v-if="loading" class="progress">
            <div class="indeterminate"></div> 
        </div>
        <h2 class="center-align black-text">Edit Order</h2>
        <div class="container" v-if="order">
            <div class="row edit-head" style="padding:20px">
                <div class="col s12 m6 l6">
                    <label>Name:</label><input type="text" v-model="order.name">
                    <label>Email ID:</label><input type="text" v-model="order.email">
                    <label>Phone:</label><input type="text" v-model="order.phone">
                </div>
                <div class="col s12 m6 l6">
                    <h6 class="grey-text indent">Order No: <span class="black-text indent">{{order.no}}</span></h6>
                    <h6 class="grey-text indent">Status: &nbsp;&nbsp;&nbsp;&nbsp; <span class="black-text indent">{{order.status}}</span></h6>
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
                    <h6 class="right-align grey-text">Total Amount: <span class="indent black-text">{{order.total}} &nbsp;&nbsp;</span></h6>
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
                    <router-link :to="{name:'ViewOrder',params: {order_no: this.order.no}}">
                    <a class="waves-effect waves-light btn-large red darken-2 right">VIEW ORDER</a>
                    </router-link>
                </div>
                <div class="input-feild col s6 m4">
                    <span class="waves-effect waves-light btn-large red darken-2 right" @click="updateOrder">SAVE ORDER</span>
                </div>
            </div>
        </div>
    </div>
</template>

<script>
import db from '@/firebase/init'
export default {
    name: 'EditOrder',
    data(){
        return {
            feedback: null,
            loading: true,
            selectedStatus: null,
            order:null,
            statusOptions: [
                'CONFIRMED',
                'ARCHIVED',
                'SENT'
            ]

        }
    },
    methods:{
        changeStatus(){
            console.log('called')
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
        updateOrder(){
            this.loading=true;
            db.collection('orders').doc(this.order.id).update(this.order).then(()=>{
                alert('Order Updated Successfully')
                this.loading=false;
                this.$router.push({name:'ViewOrder',params:{order_no:this.order.no}})            
            }).catch(err=>{
                alert('Something went wrong please try again later')
                console.log(err)
                this.loading=false;
                this.$router.push({name:'Dashboard'})       
            })
            
        }
    },
    created(){
        this.loading=true;
        let ref = db.collection('orders').where('no', '==', this.$route.params.order_no)
        ref.get().then(snapshot =>{
            if(snapshot.empty){
                alert('Cannot find the order in the database')
                this.$router.push({name: 'Dashboard'})
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
    }
}
</script>

<style>
.edit-order .indent{
    padding-left:1.8em;
    padding-right:1.8em;
}
</style>
