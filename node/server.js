/**
* Created with Prueba1.
* User: Difo
* Date: 2014-10-22
* Time: 02:28 PM
* To change this template use Tools | Templates.
*/

var cvanderito = require("socket.io").listen(6969);
cvanderito.sockets.on("connection", arranque);
console.log('Server running at http://127.0.0.1:6969/');

function arranque(usuario)
{
    
    usuario.on("nuevoNombre", emitir);
}

function emitir(data)
{
    cvanderito.sockets.emit("nombredesdeServidor", data+"*");
}