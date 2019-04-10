<template>
    <div>
        <div v-if="loading" class="progress">
            <div class="indeterminate"></div>
        </div>    
        <div v-if="product" class="edit-product container">
            <h2 class="center-align indigo-text">Edit Product</h2>
            <form @submit.prevent="editProduct"> 
        <div class="field name">
            <label for="name">Product Name</label>
            <input type="text" name="category" v-model="product.name">
        </div>
          <div class="field category">
            <label for="category">Product Category  </label>
            <input type="text" name="category" v-model="product.category">
        </div>
        <label v-if="product.sizes.length" for="Sizes">Added Sizes</label>
        <div v-for="(item,index) in product.sizes" :key="index" class="field">
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
            <button class="btn pink">Update Product</button>
        </div> 
    </form>
        </div>
        <div v-if="!product" class="edit-product container">
            <h2 class="center-align indigo-text" > {{feedbackTop}} </h2>
        </div>
    </div>
</template>

<script>
import db from '@/firebase/init'
import slugify from 'slugify'
export default {
    name: 'EditProduct',
    data(){
        return{
            product: null,
            feedbackTop: 'Loading...',
            anotherPrice: null,
            anotherSize: null,
            feedback: null,
            loading: false
        }
    },
    methods:{
        addSize(){
            if(this.anotherSize && this.anotherPrice){
                if(!isNaN(this.anotherPrice)){
                    this.feedback=null;
                    this.product.sizes.push({size: this.anotherSize, price: Number(this.anotherPrice)})
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
            this.product.sizes=this.product.sizes.filter(element => element!=size)
        },
        editProduct(){

              if(this.product.name && this.product.category && this.product.sizes.length){
                this.loading=true;
                this.feedback=null
                this.product.slug = slugify(this.product.name,{
                    replacement: '-',
                    remove: /[$*_+%~()'",!\-:@]/g,
                    lower: true
                    })
                db.collection('products').doc(this.product.id).update({
                    name: this.product.name,
                    category: this.product.category,
                    sizes: this.product.sizes,
                    image : this.product.image,
                    slug: this.product.slug
                }).then(()=>{
                    this.loading=false;
                    alert('Product Updated Sucessfully')
                    this.$router.push({name:'ProductIndex'})
                    
                }).catch(err=>{
                    alert('Something went wrong please try again later')
                    this.$router.push({name:'ProductIndex'})
                    this.loading=false;
                })
            } else{
                if(!this.product.name){
                    this.feedback='Please enter a product name'
                } else if(!this.product.category){
                    this.feedback='Please enter a product category'
                } else{
                    this.feedback ='Please enter atleast one size and price info'
                }
            }
        },
    },
    created(){
        this.loading=true;
        let ref = db.collection('products').where('slug', '==', this.$route.params.product_slug)
        ref.get().then(snapshot =>{
            if(snapshot.empty){
                
                alert('Cannot find the product in the database')
                this.$router.push({name: 'ProductsIndex'})
            } else{
                snapshot.forEach(doc => {
                    this.product = doc.data()
                    this.product.id = doc.id;
                })
            }
            this.loading=false;
           }).catch(err=>{
            console.log(err)
            this.loading=false;
        })
    }
}
</script>

<style>
.edit-product{
    margin-top: 60px;
    padding: 20px;
    max-width: 550px;
}
.edit-product h2{
    font-size: 2em;
    margin: 20px auto;

}
.edit-product .field{
    margin:20px auto;
    position:relative; 
}
.edit-product .delete{
    position: absolute;
    right: 0;
    bottom: 0;
    color: #aaa;
    font-size: 1.4em;
    cursor: pointer;
}

</style>
