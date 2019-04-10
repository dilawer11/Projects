<template>
   <div class="products">
    <div v-if="loading" class="progress">
        <div class="indeterminate"></div> 
    </div>
    <h2 class="center-align black-text">Order List</h2>
    <p class="red-text center-align" v-if="feedback">{{feedback}}</p>
    <div class="container">
        <div class="row">
            <div class="col s12 m4 l4"  v-for="order in orders" :key="order.id">
                <div class="card hoverable grey">
                    <router-link :to="{name: 'ViewOrder',params:{order_no: order.no}}">
                        <div class="card-content">
                            <h2 class="white-text">{{order.no}}</h2>
                            <h6 class="white-text">Name: {{order.name}}</h6>
                            <h6 class="white-text">Status: {{order.status}}</h6>
                            <!-- <ul class="sizes">
                                <li v-for="(item,index) in product.sizes" :key="index">
                                <span class="chip">{{item.size}} {{item.price}}</span>
                                </li> 
                            </ul> -->
                        </div>
                    </router-link>
                    <span class="btn-floating btn-large waves-effect waves-light red left halfway-fab">
                        <i class="material-icons" @click="deleteOrder(order.id)">delete</i>
                    </span>
                    <span class="btn-floating btn-large halfway-fab indigo">
                        <router-link :to="{name: 'EditOrder',params:{order_no: order.no}}">
                            <i class="material-icons edit">edit</i>
                        </router-link>
                    </span>
                </div>
            </div>
        </div>
    </div>
</div>
  
</template>

<script>
import db from '@/firebase/init'
export default {
    name: 'OrdersIndex',
    data(){
        return {
            orders:[],
            loading:true,
            feedback:null,
        }
    },
    methods:{
        deleteOrder(id){
            if(confirm('Are you sure you want to delete this order?')){
                this.loading=true
                let order = this.orders.filter(order=> order.id==order.id)
                order[0].status="ARCHIVED"
                db.collection('orders').doc(id).update(order[0]).then(()=>{
                    this.loading=false
                    alert('The product has been deleted')
                    this.orders=this.orders.filter(order => order.id!=id)
                }).catch(err=>{
                    this.loading=false
                    this.feedback="Database returned an error"
                    console.log(err)
                })
            }
        }
    },
    created(){
    //fetch data from db and update in local when created fires
        db.collection('orders').get()
        .then(snapshot => {
            this.feedback = null
            snapshot.forEach(document => {
                let order = document.data()
                order.id = document.id
                if(order.status!="ARCHIVED"){
                    this.orders.push(order)
                }
                this.orders.length? this.feedback=null : this.feedback='No orders in the database to be shown (please make sure you have a strong internet connection)'
            });
        this.loading=false
        }).catch(err=>{
            console.log(err)
            this.feedback = 'Database returned an error'
        })
    }
}
</script>

<style>

</style>
