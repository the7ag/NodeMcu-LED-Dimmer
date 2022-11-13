const express = require('express');
const app = express();
const port=3000;
app.get('/',function(req,res){
    res.sendFile(__dirname+"../FrontEnd/index.html")
});
const server =app.listen(port,function(){
console.log("Server is running on:"+port);
});

const socketServer=require('ws').Server;
const wss=new socketServer({ server });
let value=100;
wss.on('connection',function(ws){
    console.log("Client Connected")
    ws.send(value);
    ws.on('message',function(msg){
        value=msg.toString();
        wss.clients.forEach(function(client){
            if(client.readyState===client.OPEN){
                client.send(value);
            }
        })
    }); 
    ws.on('close',function(){
        console.log("Client Disconnected")
    });

});
