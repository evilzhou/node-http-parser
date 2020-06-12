var parser = require('bindings')('node-http-parser');
parser.parse({
    buffer: new Buffer(
`
POST https://m.demo.com/beauty/zh_cn/store/appletnewyear/order/placeOrder HTTP/1.1
Host: m.dior.cn
Connection: keep-alive
Content-Length: 50
Authorization: zzzzzzzzzzzzzzzzzzz
User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/53.0.2785.143 Safari/537.36 MicroMessenger/7.0.9.501 NetType/WIFI MiniProgramEnv/Windows WindowsWechat
content-type: application/json
Referer: https://servicewechat.com/wx666666666666666/38/page-frame.html
Accept-Encoding: gzip, deflate, br

{"data":{"tttttttt_customer_address_id":"1290248"}}
`
    ),
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