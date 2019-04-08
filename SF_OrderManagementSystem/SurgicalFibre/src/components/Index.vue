<template>
  <div class="index container">
    <p class="red-text" v-if="feedback">{{feedback}}</p>
    <div class="card" v-for="product in products" :key="product.id">
      <div class="card-content">
        <i class="material-icons delete " @click="deleteProduct(product.id)">delete</i>
        <h2 class="indigo-text">{{product.name}}</h2>
        <h6 class="blue-text">{{product.category}}</h6>
        <ul class="sizes">
          <li v-for="(item,index) in product.sizes" :key="index">
            <span class="chip">{{item.size}} {{item.price}}</span>
          </li> 
        </ul>
      </div>
      <span class="btn-floating btn-large halfway-fab pink">
        <router-link :to="{name: 'EditProduct',params:{product_slug: product.slug}}">
          <i class="material-icons edit">edit</i>
        </router-link>
      </span>
    </div>
  </div>
</template>

<script>
import db from '@/firebase/init'
export default {
  name: 'Index',
  data () {
    return {
      products :[],
      feedback: null
    }
  },
  methods:{
    deleteProduct(id){
      //delete product from db and update the local data
      if(confirm("Are you sure you want to delete this product?")){
        db.collection('products').doc(id).delete().then(()=>{
          alert('The product has been deleted')
          this.products=this.products.filter(product => product.id!=id)
      
        })
      }   
    },

  },
  created(){
    //fetch data from db and update in local when created fires
    db.collection('products').get()
    .then(snapshot => {
      if(snapshot.empty){
        this.feedback = 'No products in the database to be shown'
      } else{
        this.feedback = null
        snapshot.forEach(document => {
          let product = document.data()
          product.id = document.id
          this.products.push(product)
        });
      }
    })
  }
}
</script>

<!-- Add "scoped" attribute to limit CSS to this component only -->
<style>
.index{
  display : grid;
  grid-template-columns: 1fr 1fr 1fr;
  grid-gap: 30px;
  margin-top: 60px;
}
.index h2{
  font-size: 1.8em;
  text-align: center;
  margin-top: 0;  
}
.index .sizes{
  margin: 30px auto;

}
.index .sizes  li{
  display :inline-block; 
}
.index .delete{
  position: absolute;
  top:4px;
  right:4px;
  cursor:pointer;
  color:#aaa;
  font-size:1.4em;
}

</style>
