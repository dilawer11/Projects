<template>
    <div class="dashboard">
        <h2 class="center-align black-text">Dashboard</h2>
        <div class="container">
            <div class="row center-align">
                <div class="col s6 m4">
                    <div class="card hoverable grey " @click="()=>{this.$router.push({name: 'ProductsIndex'})}">
                        <div class="card-content white-text">
                        <span class="card-title">Products</span>
                        <p>View, Edit, Delete or Add new Products</p>
                        </div>
                    </div>
                </div>
                <div class="col s6 m4">
                    <div class="card hoverable grey " @click="()=>{this.$router.push({name: 'OrdersIndex'})}">
                        <div class="card-content white-text">
                        <span class="card-title">Orders</span>
                        <p>Manage, View, Edit, Delete Customer Orders</p>
                        </div>
                    </div>
                </div>
                <div class="col s6 m4">
                    <div class="card hoverable grey" @click="()=>{this.$router.push({name: 'ArchivedOrders'})}">
                        <div class="card-content white-text">
                        <span class="card-title">Archived Orders</span>
                        <p>View Archived and Deleted Orders</p>
                        </div>
                    </div>
                </div>
                <div class="col s6 m4">
                    <div class="card able grey lighten-1">
                        <div class="card-content white-text">
                        <span class="card-title ">Account Settings*</span>
                        <p>View and Change Accounts Settings (*currently disabled)
                        </p>
                        </div>
                    </div>
                </div>
            </div>
        </div>
    </div>
</template>

<script>
export default {
    name: 'Dashboard',
    data(){
        return{

        }
    }
}
</script>

<style>
.dashboard .card{
    cursor: pointer;
    padding:20px;
    margin-top:20px 50px;
    height:250px;
}
</style>
