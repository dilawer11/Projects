module.exports = {
    pages:{
        admin:{
            entry: 'src/admin/main.js',
            template:'public/admin.html',
            filename:'admin.html',
            title:'Admin Panel',
            // chunks: ['chunk-vendors', 'chunk-common', 'index']
        },
        index:{
            entry: 'src/index/main.js',
            template:'public/index.html',
            filename:'index.html',
            title:'Client Page'
        }
    }
}