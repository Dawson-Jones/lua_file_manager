#include <stdio.h>
#include <string.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include "auth.h"

static char const *dictionary = "ATTRIBUTE	Login-Service		15	integer\
|ATTRIBUTE	Login-TCP-Port		16	integer\
|ATTRIBUTE	Reply-Message		18	string\
|ATTRIBUTE	Callback-Number		19	string\
|ATTRIBUTE	Callback-Id		20	string\
|ATTRIBUTE	Framed-Route		22	string\
|ATTRIBUTE	Framed-IPX-Network	23	ipaddr\
|ATTRIBUTE	State			24	string\
|ATTRIBUTE	Class			25	string\
|ATTRIBUTE	Vendor-Specific		26	string\
|ATTRIBUTE	Session-Timeout		27	integer\
|ATTRIBUTE	Idle-Timeout		28	integer\
|ATTRIBUTE	Termination-Action	29	integer\
|ATTRIBUTE	Called-Station-Id	30	string\
|ATTRIBUTE	Calling-Station-Id	31	string\
|ATTRIBUTE	NAS-Identifier		32	string\
|ATTRIBUTE	Proxy-State		33	string\
|ATTRIBUTE	Login-LAT-Service	34	string\
|ATTRIBUTE	Login-LAT-Node		35	string\
|ATTRIBUTE	Login-LAT-Group		36	string\
|ATTRIBUTE	Framed-AppleTalk-Link	37	integer\
|ATTRIBUTE	Framed-AppleTalk-Network	38	integer\
|ATTRIBUTE	Framed-AppleTalk-Zone	39	string\
|ATTRIBUTE	Acct-Status-Type	40	integer\
|ATTRIBUTE	Acct-Delay-Time		41	integer\
|ATTRIBUTE	Acct-Input-Octets	42	integer\
|ATTRIBUTE	Acct-Output-Octets	43	integer\
|ATTRIBUTE	Acct-Session-Id		44	string\
|ATTRIBUTE	Acct-Authentic		45	integer\
|ATTRIBUTE	Acct-Session-Time	46	integer\
|ATTRIBUTE	Acct-Input-Packets	47	integer\
|ATTRIBUTE	Acct-Output-Packets	48	integer\
|ATTRIBUTE	Acct-Terminate-Cause	49	integer\
|ATTRIBUTE	Acct-Multi-Session-Id	50	string\
|ATTRIBUTE	Acct-Link-Count		51	integer\
|ATTRIBUTE	Acct-Input-Gigawords	52	integer\
|ATTRIBUTE	Acct-Output-Gigawords	53	integer\
|ATTRIBUTE	Event-Timestamp		55	integer\
|ATTRIBUTE	CHAP-Challenge		60	string\
|ATTRIBUTE	NAS-Port-Type		61	integer\
|ATTRIBUTE	Port-Limit		62	integer\
|ATTRIBUTE	Login-LAT-Port		63	integer\
|ATTRIBUTE	Connect-Info		77	string\
|ATTRIBUTE 	EAP-Message    		79   string\
|ATTRIBUTE 	Message-Authenticatior  80  string\
|ATTRIBUTE	NAS-IPv6-Address	95	string\
|ATTRIBUTE	Framed-Interface-Id	96	string\
|ATTRIBUTE	Framed-IPv6-Prefix	97	ipv6prefix\
|ATTRIBUTE	Login-IPv6-Host		98	string\
|ATTRIBUTE	Framed-IPv6-Route	99	string\
|ATTRIBUTE	Framed-IPv6-Pool	100	string\
|ATTRIBUTE	Framed-IPv6-Address	168	ipv6addr\
|ATTRIBUTE	DNS-Server-IPv6-Address	169	ipv6addr\
|ATTRIBUTE	Route-IPv6-Information	170	ipv6prefix\
|ATTRIBUTE	Huntgroup-Name		221	string\
|ATTRIBUTE	User-Category		1029	string\
|ATTRIBUTE	Group-Name		1030	string\
|ATTRIBUTE	Simultaneous-Use	1034	integer\
|ATTRIBUTE	Strip-User-Name		1035	integer\
|ATTRIBUTE	Fall-Through		1036	integer\
|ATTRIBUTE	Add-Port-To-IP-Address	1037	integer\
|ATTRIBUTE	Exec-Program		1038	string\
|ATTRIBUTE	Exec-Program-Wait	1039	string\
|ATTRIBUTE	Hint			1040	string\
|ATTRIBUTE	Expiration		  21	date\
|ATTRIBUTE	Auth-Type		1000	integer\
|ATTRIBUTE	Menu			1001	string\
|ATTRIBUTE	Termination-Menu	1002	string\
|ATTRIBUTE	Prefix			1003	string\
|ATTRIBUTE	Suffix			1004	string\
|ATTRIBUTE	Group			1005	string\
|ATTRIBUTE	Crypt-Password		1006	string\
|ATTRIBUTE	Connect-Rate		1007	integer\
|VALUE		Service-Type		Login-User		1\
|VALUE		Service-Type		Framed-User		2\
|VALUE		Service-Type		Callback-Login-User	3\
|VALUE		Service-Type		Callback-Framed-User	4\
|VALUE		Service-Type		Outbound-User		5\
|VALUE		Service-Type		Administrative-User	6\
|VALUE		Service-Type		NAS-Prompt-User		7\
|VALUE		Service-Type		Authenticate-Only	8\
|VALUE		Service-Type		Callback-NAS-Prompt	9\
|VALUE		Service-Type		Call-Check		10\
|VALUE		Service-Type		Callback-Administrative	11\
|VALUE		Framed-Protocol		PPP			1\
|VALUE		Framed-Protocol		SLIP			2\
|VALUE		Framed-Protocol		ARAP			3\
|VALUE		Framed-Protocol		GANDALF-SLMLP		4\
|VALUE		Framed-Protocol		XYLOGICS-IPX-SLIP	5\
|VALUE		Framed-Protocol		X75			6\
|VALUE		Framed-Routing		None			0\
|VALUE		Framed-Routing		Broadcast		1\
|VALUE		Framed-Routing		Listen			2\
|VALUE		Framed-Routing		Broadcast-Listen	3\
|VALUE		Framed-Compression	None			0\
|VALUE		Framed-Compression	Van-Jacobson-TCP-IP	1\
|VALUE		Framed-Compression	IPX-Header		2\
|VALUE		Framed-Compression	Stac-LZS		3\
|VALUE		Login-Service		Telnet			0\
|VALUE		Login-Service		Rlogin			1\
|VALUE		Login-Service		TCP-Clear		2\
|VALUE		Login-Service		PortMaster		3\
|VALUE		Login-Service		LAT			4\
|VALUE		Login-Service		X.25-PAD		5\
|VALUE		Login-Service		X.25-T3POS		6\
|VALUE		Login-Service		TCP-Clear-Quiet		8\
|VALUE		Acct-Status-Type	Start			1\
|VALUE		Acct-Status-Type	Stop			2\
|VALUE		Acct-Status-Type	Alive			3\
|VALUE		Acct-Status-Type	Accounting-On		7\
|VALUE		Acct-Status-Type	Accounting-Off		8\
|VALUE		Acct-Authentic		RADIUS			1\
|VALUE		Acct-Authentic		Local			2\
|VALUE		Acct-Authentic		Remote			3\
|VALUE		Termination-Action	Default			0\
|VALUE		Termination-Action	RADIUS-Request		1\
|VALUE		NAS-Port-Type		Async			0\
|VALUE		NAS-Port-Type		Sync			1\
|VALUE		NAS-Port-Type		ISDN			2\
|VALUE		NAS-Port-Type		ISDN-V120		3\
|VALUE		NAS-Port-Type		ISDN-V110		4\
|VALUE		NAS-Port-Type		Virtual			5\
|VALUE		NAS-Port-Type		PIAFS			6\
|VALUE		NAS-Port-Type		HDLC-Clear-Channel	7\
|VALUE		NAS-Port-Type		X.25			8\
|VALUE		NAS-Port-Type		X.75			9\
|VALUE		NAS-Port-Type		G.3-Fax			10\
|VALUE		NAS-Port-Type		SDSL			11\
|VALUE		NAS-Port-Type		ADSL-CAP		12\
|VALUE		NAS-Port-Type		ADSL-DMT		13\
|VALUE		NAS-Port-Type		IDSL			14\
|VALUE		NAS-Port-Type		Ethernet		15\
|VALUE           Acct-Terminate-Cause    User-Request            1\
|VALUE           Acct-Terminate-Cause    Lost-Carrier            2\
|VALUE           Acct-Terminate-Cause    Lost-Service            3\
|VALUE           Acct-Terminate-Cause    Idle-Timeout            4\
|VALUE           Acct-Terminate-Cause    Session-Timeout         5\
|VALUE           Acct-Terminate-Cause    Admin-Reset             6\
|VALUE           Acct-Terminate-Cause    Admin-Reboot            7\
|VALUE           Acct-Terminate-Cause    Port-Error              8\
|VALUE           Acct-Terminate-Cause    NAS-Error               9\
|VALUE           Acct-Terminate-Cause    NAS-Request             10\
|VALUE           Acct-Terminate-Cause    NAS-Reboot              11\
|VALUE           Acct-Terminate-Cause    Port-Unneeded           12\
|VALUE           Acct-Terminate-Cause    Port-Preempted          13\
|VALUE           Acct-Terminate-Cause    Port-Suspended          14\
|VALUE           Acct-Terminate-Cause    Service-Unavailable     15\
|VALUE           Acct-Terminate-Cause    Callback                16\
|VALUE           Acct-Terminate-Cause    User-Error              17\
|VALUE           Acct-Terminate-Cause    Host-Request            18\
|VALUE		Auth-Type		Local			0\
|VALUE		Auth-Type		System			1\
|VALUE		Auth-Type		SecurID			2\
|VALUE		Auth-Type		Crypt-Local		3\
|VALUE		Auth-Type		Reject			4\
|VALUE		Auth-Type		Pam			253\
|VALUE		Auth-Type		Accept			254\
|VALUE		Fall-Through		No			0\
|VALUE		Fall-Through		Yes			1\
|VALUE		Add-Port-To-IP-Address	No			0\
|VALUE		Add-Port-To-IP-Address	Yes			1\
|ATTRIBUTE	Login-IP-Host		14	ipaddr\
|ATTRIBUTE	Framed-Compression	13	integer\
|ATTRIBUTE	Framed-MTU		12	integer\
|ATTRIBUTE	Filter-Id		11	string\
|ATTRIBUTE	Framed-Routing		10	integer\
|ATTRIBUTE	Framed-IP-Netmask	9	ipaddr\
|ATTRIBUTE	Framed-IP-Address	8	ipaddr\
|ATTRIBUTE	Framed-Protocol		7	integer\
|ATTRIBUTE	Service-Type		6	integer\
|ATTRIBUTE	NAS-Port-Id 	5	integer\
|ATTRIBUTE	NAS-IP-Address		4	ipaddr\
|ATTRIBUTE	CHAP-Password		3	string\
|ATTRIBUTE	Password		2	string\
|ATTRIBUTE	User-Name		1	string";
//最后10多个经常用到，因为插入到链表中时，是插入到前面的，所以我把它们放在字符串最后，保证每次查找不会
//耽误太多时间

int table_to_string(lua_State* L,int index,char *save_string)
{	
	//printf("yundun开始解析表\n");
	char const* key = NULL;
	char const* value = NULL;
	int not_empty = 0;
	
	lua_pushnil(L);	
	while(lua_next(L, index))  
	{  
		not_empty = 1;

		key = lua_tostring(L,-2);
		
		if (lua_isstring(L,-1))
		{
			strcat(save_string,key);
			strcat(save_string," ");
			
			value = lua_tostring(L,-1);
			strcat(save_string,value);
			strcat(save_string,"|");			
		}
		else if(lua_istable(L,-1))
		{
			int i = 1;
			int size = lua_objlen(L,-1);
			char const* sub_value = NULL;
			for(i; i <= size; i++)	
			{  
				lua_pushnumber(L, i);  
				lua_gettable(L, -2); 
				sub_value = lua_tostring(L,-1);
				
				strcat(save_string,key);
				strcat(save_string," ");
				strcat(save_string,sub_value);
				strcat(save_string,"|");	
				lua_pop(L, 1);	
			}	
		}
		else
		{
			return -1;
		}
		
		lua_pop(L, 1);
		char const * temp = lua_tostring(L,-1);
	}  

	if (not_empty && save_string[strlen(save_string) -1] == '|')
	{
		save_string[strlen(save_string) -1] = '\0'; 
	}
	
	//printf("yundun解析表的结果是%s\n",save_string);
	return 0;
	
}

static int radiusauth(lua_State* L)
{
	if (!lua_isstring(L,1)){
		lua_pushnumber(L,-3);
		lua_pushstring(L,"the 1st param should be string");
		return 2;
	}

	if (!lua_isstring(L,2)){
		lua_pushnumber(L,-3);
		lua_pushstring(L,"the 2nd param should be string");
		return 2;
	}

	if (!lua_istable(L,3)){
		lua_pushnumber(L,-3);
		lua_pushstring(L,"the 3rd param should be table");
		return 2;
	}

	if (!lua_istable(L,4)){
		lua_pushnumber(L,-3);
		lua_pushstring(L,"the 4th param should be table");
		return 2;
	}

	if (!lua_isnumber(L,5)){
		lua_pushnumber(L,-3);
		lua_pushstring(L,"the 5th param should be number");
		return 2;
	}

	
	//用户名
	char user_name[128] = {'\0'};
	char const *input_name = lua_tostring(L,1);
	strcpy(user_name,input_name);
	//密码
	char user_password[128] = {'\0'};
	char const *input_password = lua_tostring(L,2);
	strcpy(user_password,input_password);

	int table_res = 0;

	//配置
	char client_config[4096] = {'\0'};
	table_res = table_to_string(L,3,client_config);
	if (table_res != 0)
	{
		lua_pushnumber(L,-3);
		lua_pushstring(L,"param error");
		return 2;
	}

	//共享秘钥
	char servers_secrets[1024] = {'\0'};
	table_res = table_to_string(L,4,servers_secrets);
	if (table_res != 0)
	{
		lua_pushnumber(L,-3);
		lua_pushstring(L,"param error");
		return 2;
	}

	//message-authenticator
	const int use_MA = lua_tonumber(L,5);

	char *auth_msg = "";
	
	int auth_res = auth(user_name,user_password,
						(char const *)client_config, dictionary,servers_secrets,use_MA,&auth_msg);

	//printf("yundun认证结果是%i,%s\n",auth_res,auth_msg);
	
	lua_pushnumber(L,auth_res);
	lua_pushstring(L,auth_msg);
	
	return 2;
}

static luaL_Reg radiusfuncs[] = {
	{"radiusauth",radiusauth},
	{NULL,NULL}
};


int luaopen_radiusclient(lua_State* L) 
{
	const char *libname = "radiusclient";
	luaL_register(L,libname,radiusfuncs);
	return 1;
}
