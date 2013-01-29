var console = require("./routine_js/lib.js");
function main()
{
	routine.On("message",function (src,msg){
		console.log("sdf");
	});
	routine.On("exit",function (code){
		console.log("[ADD]-SELF-EXIT",code);
	});
	routine.parent.On("message",function (msg){
		console.log('[ADD]-PARENT-MESSAGE',msg);
		var data = JSON.parse(msg.data);
		var ret = data.a+data.b;
		if(msg.session){
			routine.parent.Responce({data:ret,type:1},msg.session);
		}
	});
	routine.parent.On("exit",function(code){
		console.log("[ADD]-PARENT-EXIT",code);
	});
	startTcpSvr("127.0.0.1",8195,'epoll',routine.rid,2);
	
}
main();


function startTcpSvr(ip,port,mode,watchdog,headsz){
	const TCP_MSG_TYPE={
		CONNECT:0X01,
		MESSAGE:0X02,
		CLOSE:0X03,
	};
	//mode = 'select' 'epoll';
	var size = 0;
	var num_pkt = 0;
	var tcpSvr = routine.Spawn("tcpsvr","mode="+mode+"&ip="+ip+"&port="+port+"&watchdog="+watchdog+"&headsz="+headsz);
	if(tcpSvr){
		var num=0;
		tcpSvr.On("message",function(msg){
			if(msg.type == TCP_MSG_TYPE.CONNECT){
				console.log("tcpSvr-Msg",port,"new_connect",++num);
			}else if(msg.type == TCP_MSG_TYPE.MESSAGE){
				//console.log("tcpSvr-Msg",msg,msg.data.length-4,num_pkt++);
				var str = msg.data;
				size+=msg.data.length-4;
				num_pkt++
			}else if(msg.type == TCP_MSG_TYPE.CLOSE){
				console.log("tcpSvr-Msg",port,"connect_close",--num);	
				console.log("tcpSvr-ALL-INFO",num_pkt,size);
			}else{
				console.log("unknow info");
			}
		});
		tcpSvr.On("exit",function(code){
			console.log("tcpSvr,exit",code);
		 });
		var pre = new Date().getTime();
		routine.Timer(function(){
			var now = new Date().getTime();
			console.log("add.js",now-pre);
			pre = now;
			print("[SIZE:]",size/1024/1024,"Mb;","[NUM_PKT:]",num_pkt);
			size = 0;
			num_pkt = 0;
		},10.0);
	}else{
		console.log("tcp-svr-launch failed");
		throw new Error("tcp-svr-lanuch-failed");
	}
}
