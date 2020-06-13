var parser = require('bindings')('node-http-parser');
parser.parse({
    buffer: Buffer.from(
`GET https://m.demo.com/beauty/zh_cn/store/placeOrder HTTP/1.1
Host: m.dior.cn
Connection: keep-alive
Content-Length: 3
Authorization: zzzzzzzzzzzzzzzzzzz
User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/53.0.2785.143 Safari/537.36 MicroMessenger/7.0.9.501 NetType/WIFI MiniProgramEnv/Windows WindowsWechat
content-type: text/plain
Referer: https://servicewechat.com/wx666666666666666/38/page-frame.html
Accept-Encoding: gzip, deflate, br

111`, 'utf-8'),
    headers: [],
    on_message_begin: function(){
        console.log('--------------------------------');
    },
    on_url: function(url){
        console.log(url);
    },
    on_header_field: function(field){
        this.headers.push(field);
    },
    on_header_value: function(value){
        this.headers.push(value);
    },
    on_headers_complete: function(){
        for(let i=0; i<this.headers.length/2; i++){
            console.log(this.headers[i*2] + ': ' + this.headers[i*2+1]);
        }
    },
    on_body: function(buffer){
        console.log(buffer.toString('utf-8'));
    },
    on_message_complete: function(){
        console.log("================================");
    }
});

parser.parse({
    buffer: Buffer.from(
'HTTP/1.1 200 OK\r\n' +
'Date: Wed, 06 Jul 2016 06:59:55 GMT\r\n'+
'Server: Apache\r\n'+
'Accept-Ranges: bytes\r\n'+
'Transfer-Encoding: chunked\r\n'+
'Content-Type: text/html\r\n'+
'Content-Encoding: gzip\r\n'+
'Connection: keep-alive\r\n'+
'\r\n'+
'3\r\n'+
'111\r\n'+
'4\r\n'+
'2222\r\n'+
'0\r\n'+
'\r\n', 'utf-8'),
    headers: [],
    on_message_begin: function(){
        console.log('--------------------------------');
    },
    on_status: function(status){
        console.log(`status: ${status}`);
    },
    on_header_field: function(field){
        this.headers.push(field);
    },
    on_header_value: function(value){
        this.headers.push(value);
    },
    on_headers_complete: function(){
        for(let i=0; i<this.headers.length/2; i++){
            console.log(this.headers[i*2] + ': ' + this.headers[i*2+1]);
        }
    },
    on_body: function(buffer){
        console.log(buffer.toString('utf-8'));
    },
    on_message_complete: function(){
        console.log("================================");
    },
    on_chunk_header: function(){
        console.log('--------new chunk--------');
    },
    on_chunk_complete: function(){
        console.log('-------chunk done--------');
    }
});