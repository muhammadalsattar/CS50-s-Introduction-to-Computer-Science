const path = require('path')
const express = require('express')
const app = express()
const staticPath = path.join(__dirname, '..', 'public/static')
const port = process.env.PORT || 3000
const favicon = require('serve-favicon')


app.use(express.static(staticPath))
app.use(favicon(path.join(__dirname, '..', '/public/favicon.ico')))


app.get('*', (req, res)=> {
    res.sendFile(path.join(__dirname, '..', '/public/index.html'))

})

app.listen(port, () => {
    console.log('server is running!')
})