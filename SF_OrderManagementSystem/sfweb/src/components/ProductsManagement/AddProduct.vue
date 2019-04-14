<template>
<div>
    <div v-if="loading" class="progress">
        <div class="indeterminate"></div>
    </div>   
    <h2 class="center-align black-text">Add New Product</h2> 
    <div class="add-product container">
    
    <form @submit.prevent="addProduct"> 
        <div class="field name">
            <label for="name">Product Name</label>
            <input type="text" name="category" v-model="name">
        </div>
          <div class="field category">
            <label for="category">Product Category  </label>
            <input type="text" name="category" v-model="category">
        </div>
        <label v-if="sizes.length" for="Sizes">Added Sizes</label>
        <div v-for="(item,index) in sizes" :key="index" class="field">
            <h6> Size: {{item.size}}  Price : Rs.{{item.price}} </h6>
            <!-- <input type="text" name="size" v-model="sizes[index].size"> -->
            <!-- <input type="text" name="price" v-model="sizes[index].price"> -->
            <i class="material-icons delete" @click="deleteSize(item)">delete </i>
        </div>
       
        <div class="field add-sizes">
            <label for="add-sizes">Size</label>
            <input type="text" name="add-size" v-model="anotherSize">
            <label for="add-sizes">Price</label>
            <input type="text" name="add-price" @keydown.tab.prevent="addSize" v-model="anotherPrice">
        </div>
         <div class="btn-small pink add-sizes-button center-align" @click="addSize">
            <i class="material-icons">add</i>
        </div> 
        <p v-if="feedback" class="red-text">{{feedback}}<p>
        <div class="field center-align">
            <button class="btn pink">Add Product</button>
        </div> 
    </form>
</div>
</div>
</template>

<script>
import db from '@/firebase/init'
import slugify from 'slugify'
export default {
    name: 'AddProduct',
    data(){
        return{
            name: null,
            category:null,
            sizes:[],
            anotherSize: null,
            anotherPrice: null,
            feedback: null,
            slug: null,
            loading:false,
        }
    },
    methods:{
        addProduct(){
            if(this.name && this.category && this.sizes.length){
                this.loading=true;
                this.feedback=null
                this.slug = slugify(this.name,{
                    replacement: '-',
                    remove: /[$*_+%~()'",!\-:@]/g,
                    lower: true
                })
                db.collection('products').add({
                    name: this.name,
                    category: this.category,
                    sizes: this.sizes,
                    image : 'none',
                    slug: this.slug

                }).then(()=>{
                    this.loading=false;
                    alert('Product Added Sucessfully')
                    this.$router.push({name:'ProductIndex'})
                }).catch(err=>{
                    this.loading=false;
                    alert('Something went wrong please try again later')
                    this.$router.push({name:'ProductIndex'})
                })
            } else{
                if(!this.name){
                    this.feedback='Please enter a product name'
                } else if(!this.category){
                    this.feedback='Please enter a product category'
                } else{
                    this.feedback ='Please enter atleast one size and price info'
                }
            }
        },
        addSize(){
            if(this.anotherSize && this.anotherPrice){
                if(!isNaN(this.anotherPrice)){
                    this.feedback=null;
                    this.sizes.push({size: this.anotherSize, price: Number(this.anotherPrice)})
                    this.anotherSize=null;
                    this.anotherPrice=null;
                }
                else{
                    this.feedback = 'Price must be a number'
                }
            } else{
                this.feedback = 'You must enter a value'
            }
        },
        deleteSize(size){
            this.sizes=this.sizes.filter(element => element!=size)
        }
    }

}
</script>

<style>
.add-product{
    margin-top: 60px;
    padding: 20px;
    max-width: 550px;
}
.add-product h2{
    font-size: 2em;
    margin: 20px auto;

}
.add-product .field{
    margin:20px auto;
    position:relative; 
}
.add-product .delete{
    position: absolute;
    right: 0;
    bottom:0;
    color: #aaa;
    font-size: 1.4em;
    cursor: pointer;
}

</style>
