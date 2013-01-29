/*
 * js_main.cc
 *
 *  Created on: 2012-11-12
 *      Author: goalworld
 */



#include "jsv8.h"
#include <stdlib.h>
#include <rain.h>
#include <string>
#include <iostream>
using namespace v8;
extern "C"{

void *
jsv8_init(rain_ctx_t *ctx,const char *args)
{
	jsv8_t * js = new jsv8_t();
	if( js->Initialize(ctx,args) ){
		return js;
	}else{
		delete  js;
		return NULL;
	}

}
void
jsv8_destroy(void *env,int code)
{
	jsv8_t * js = (jsv8_t *)env;
	js->Exit(code);
	delete js;
}
}
