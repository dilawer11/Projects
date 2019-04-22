<template>
    <div class="edit-order">
        <div v-if="loading" class="progress">
            <div class="indeterminate"></div> 
        </div>
       
        <h2 class="center-align black-text">Edit Order</h2>
        <div class="container" v-if="order && products.length">
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
                                <th></th>
                            </tr>
                        </thead>
                        <tbody>
                            <tr v-for="(item,itemIndex) in order.items" :key="itemIndex" >
                                <td>
                                    <select v-model="item.name" @change="updateItemName(itemIndex)" class="browser-default">
                                        <option selected>{{item.name}}</option>
                                        <option v-for="(product,i) in products.filter(product=>product.name!=item.name)" :key="i">{{product.name}}</option>
                                    </select>
                                </td>
                                <td>
                                    <input type="text" @change="updateItemTotal(itemIndex)" v-model="item.quantity">
                                </td>
                                <td>
                                    <select v-model="item.size" @change="updateItemSize(itemIndex)" class="browser-default">
                                        <option selected>{{item.size}}</option>
                                        <option v-for="(element,i) in products[findProductbyName(item.name)].sizes.filter(sizeObj=>sizeObj.size!=item.size)" :key="i">{{element.size}}</option>
                                    </select>
                                </td>
                                <td>{{item.price}}</td>
                                <td>{{item.total}}</td>
                                <td><i @click="deleteItem(itemIndex)" class="material-icons">delete</i></td>
                            </tr>
                        </tbody>
                    </table>
                    <br>
                    <h6 class="right-align grey-text">Total Amount: <span class="indent black-text">{{totalAmount}} &nbsp;&nbsp;</span></h6>
                </div>
            </div>
             <p class="center-align red-text" v-if="feedback">{{feedback}}</p>
            <div class="row status">
                <div class="input-feild col s6 m4">
                    <select v-model="selectedStatus" @change="changeStatus" class="browser-default">
                        <option value="" disabled selected> Choose a status</option>
                        <option v-for="(item,i) in statusOptions" :key="i">{{item}}</option>
                    </select>
                    <label>Change Status</label> 
                </div>
                <div class="input-feild col s6 m4">
                    <span class="waves-effect waves-light btn-large red darken-2 right" @click="goToView()">VIEW ORDER</span>
                </div>
                <div class="input-feild col s6 m4">
                    <span class="waves-effect waves-light btn-large red darken-2 right" @click="updateOrder()">SAVE ORDER</span>
                </div>
            </div>
        </div>
    </div>
</template>

<script>
import db from '@/firebase/init'
import { mapState } from 'vuex'
export default {
    name: 'EditOrder',
    data(){
        return {
            feedback: null,
            loading: true,
            selectedStatus: null,
            order:null,
            products: [],
        }
    },
    methods:{
   
        changeStatus(){
            if(this.selectedStatus!=this.order.status){
                this.loading=true;
                this.order.status=this.selectedStatus;
                // db.collection('orders').doc(this.order.id).update(this.order).then(()=>{
                //     this.loading=false;            
                // }).catch(err=>{
                //     alert('Something went wrong please try again later')
                //     console.log(err)
                //     this.loading=false;
                // })
            }
        },
        validateOrder(){
            //TODO: Validate Other Feilds
            let passed=true;
            //Order Items Validation
            this.order.items.forEach(item=>{
                if(!item.name){
                    this.feedback = 'Please Select an Item Name'
                    passed=false;
                } else if(isNaN(item.quantity) || item.quantity<=0 || item.quanity >= 99999){
                    this.feedback = 'Please enter quanity between 0 and 99999';
                    console.log("failed")
                    passed=false;
                } else if(!item.size){
                    this.feedback = 'Please Select and Item Size'
                    passed=false
                }
            })
            if(passed){
                this.feedback=null
            }
            return passed;
        },
        updateOrder(){
            this.loading=true;
            if(this.validateOrder()){
                if(confirm('Are you sure you want to edit the order?')){
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
            }
            this.loading=false;
            
        },
        goToView(){
            if(confirm('Are you sure you want to leave this page? Any unsaved changes will be lost')){
                this.$router.push({name:'ViewOrder',params: {order_no: this.order.no}})
            }
        },
        deleteItem(index){
            this.order.items.splice(index,1)
        },
        findProductbyName(name){
            return this.products.findIndex((product)=>product.name==name);
        },
        findSizebyName(name,index){
            return this.products[index].sizes.findIndex(element=>element.size==name);
        },
        updateItemName(index){
            // this.order.items[index].size = this.products[this.findProductbyName(this.order.items[index].name)].sizes[0].size;
            this.order.items[index].size = null;
            this.updateItemSize(index)
            this.updateItemTotal(index);
        },
        updateItemSize(index){
            if(this.order.items[index].size){
                this.order.items[index].price= this.products[this.findProductbyName(this.order.items[index].name)].sizes[this.findSizebyName(this.order.items[index].size,this.findProductbyName(this.order.items[index].name))].price;
            }
            else{
                this.order.items[index].price=0;
            }
            this.updateItemTotal(index);
        },
        updateItemTotal(index){
            this.order.items[index].total=this.order.items[index].quantity*this.order.items[index].price
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
        db.collection('products').get().then(snap=>{
            snap.forEach(doc=>{
                this.products.push(doc.data())
            })
        })
    },
    computed:{
        ...mapState(['statusOptions']),
        totalAmount: function (){
            return this.order.items.reduce((num,item)=>item.total+num,0)
        },
    },
   
}
</script>

<style>
.edit-order .indent{
    padding-left:1.8em;
    padding-right:1.8em;
}
</style>
