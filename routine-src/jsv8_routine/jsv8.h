/*
 * jsv8_rain.h
 *
 *  Created on: 2012-11-10
 *      Author: goalworld
 */

#ifndef JSV8_RAIN_H_
#define JSV8_RAIN_H_

#include <v8.h>
#include <string>
#include <rain.h>
#include <map>
#include <set>
extern "C"{
struct jsv8_ctx_t;
class jsv8_t
{
public:
	static v8::Handle<v8::Value> Spawn(const v8::Arguments& args);
	static v8::Handle<v8::Value> On(const v8::Arguments& args);
	static v8::Handle<v8::Value> Exit(const v8::Arguments& args);
	static v8::Handle<v8::Value> Timer(const v8::Arguments& args);
private:
	static  void _recv(void *arg,routine_t src,rain_msg_t msg,session_t session);
	static  void _recv_rsp(void *arg,routine_t src,rain_msg_t msg,session_t session);
	static  void _link(void *arg,routine_t exit,int code);
	static  void _next_tick(void *arg,void *userdata);
	static  void _time_out(void *arg,void *userdata);
public:
	jsv8_t();
	~jsv8_t();
	bool Initialize(rain_ctx_t *ctx,const std::string & args);
	void Exit(int code);
private:
	int Run();
	v8::Handle<v8::Object> SteupRoutine(const std::string & args);
	void Recv(routine_t src,rain_msg_t msg,session_t session);
	void RecvResponce(routine_t src,rain_msg_t msg,session_t session);
	void Link(routine_t exit,int code);
	typedef std::map<long,jsv8_ctx_t *> RelationMap;
	typedef RelationMap::iterator RelationMapIter;
	RelationMap relates_;
	rain_ctx_t* ctx_;
	struct timer{
		int repeat_;
		v8::Persistent<v8::Function> cb_;
		double times_;
	};
	typedef std::map<uint32_t,timer> TimerMap;
	typedef TimerMap::iterator TimerMapIter;
	TimerMap timers_;
	uint32_t timeid_;
	//v8::Persistent<v8::Object> routine_;
	v8::Persistent<v8::Function> recv_;
	v8::Persistent<v8::Function> exit_;
	v8::Persistent<v8::Context> v8ctx_;
	v8::Isolate * solt_;
	v8::Persistent<v8::Function> start_;

	v8::Persistent<v8::Value> parent_;
	v8::Persistent<v8::Value> routine_;
	bool bStart;
};

}
#endif /* JSV8_RAIN_H_ */
