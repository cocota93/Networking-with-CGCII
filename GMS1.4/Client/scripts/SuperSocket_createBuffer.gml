///SuperSocket_createBuffer(Size, Signal);

if(argument1 == SuperSocket.SendToClient){
    global.buffer_mode = true;
}

var buffer = buffer_create(argument0, buffer_grow, 1);
buffer_write(buffer, buffer_u32, 0);
buffer_write(buffer, buffer_u32, argument1); // signal
return buffer;
