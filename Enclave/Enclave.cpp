#include "Enclave.h"
#include "tSgxSSL_api.h"
#include "ec.h"
#include "obj_mac.h"
#include "bn.h"
#include "ebcdic.h"
#include "ecdsa.h"
#include <stdio.h>

#define ECDH_SIZE 33
/*Sm2 中指定的参数 确定下y2 = x3 + ax + b 曲线*/
#define _P  "FFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00000000FFFFFFFFFFFFFFFF"

#define _a  "FFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00000000FFFFFFFFFFFFFFFC"

#define _b  "28E9FA9E9D9F5E344D5A9E4BCF6509A7F39789F515AB8F92DDBCBD414D940E93"

#define _n  "FFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFF7203DF6B21C6052B53BBF40939D54123"

#define _Gx "32C4AE2C1F1981195F9904466A39C9948FE30BBFF2660BE1715A4589334C74C7"

#define _Gy "BC3736A2F4F6779C59BDCEE36B692153D0A9877CC62A474002DF32E52139F0A0"

void printf(const char *fmt, ...)
{
	char buf[BUFSIZ] = {'\0'};
	va_list ap;
	va_start(ap, fmt);
	vsnprintf(buf, BUFSIZ, fmt, ap);
	va_end(ap);
	ocall_print_string(buf);
}

void log(int level, const char *info){
    ocall_log(level, info);
}


void handleErrors()
{
	printf("Error occurred.\n");
}

static void disp(const char *str, const void *pbuf, const int size)
{
	int i=0;
	if(str != NULL){
		printf("%s:\n", str);
	}
	if(pbuf != NULL && size > 0){
		for(i=0;i<size;i++)
			printf("%02x ", *((unsigned char *)pbuf+i));
		printf("\n");
	}
	printf("\n");
}


void ecall_say_hello(const char *name, size_t namelen){
	const char * ssl_version = SGXSSLGetSgxSSLVersion();

	EC_KEY *ecdh = EC_KEY_new();
	const EC_POINT *point = NULL;
	EC_POINT *point2c;
	const EC_GROUP *group;
	unsigned char pubkey[ECDH_SIZE];
	unsigned char shared[ECDH_SIZE];
	int len;
 
	//Generate Public
	ecdh = EC_KEY_new_by_curve_name(NID_X9_62_prime256v1);//NID_secp521r1
	EC_KEY_generate_key(ecdh);
	point = EC_KEY_get0_public_key(ecdh);
	group = EC_KEY_get0_group(ecdh);
 
	if(0 == (len = EC_POINT_point2oct(group, point, POINT_CONVERSION_COMPRESSED, pubkey, ECDH_SIZE, NULL))) handleErrors();
	printf("len=%d\n",len);
 
	/* bob */
	EC_KEY *ecdh2 = EC_KEY_new();
	const EC_POINT *point2 = NULL;
	EC_POINT *pointc;
	const EC_GROUP *group2;
	unsigned char pubkey2[ECDH_SIZE];
	unsigned char shared2[ECDH_SIZE];
	int len2;
 
	//Generate Public
	ecdh2 = EC_KEY_new_by_curve_name(NID_X9_62_prime256v1);//NID_secp521r1
	EC_KEY_generate_key(ecdh2);
	point2 = EC_KEY_get0_public_key(ecdh2);
	group2 = EC_KEY_get0_group(ecdh2);
	
	if(0 == (len2 = EC_POINT_point2oct(group2, point2, POINT_CONVERSION_COMPRESSED, pubkey2, ECDH_SIZE, NULL))) handleErrors();
	printf("len2=%d\n",len);
 
	/* alice */
	//ComputeKey
	point2c = EC_POINT_new(group);
	EC_POINT_oct2point(group, point2c, pubkey2, ECDH_SIZE, NULL);
 
	if (0 != EC_POINT_cmp(group, point2, point2c, NULL)) handleErrors();
	if(0 == (len = ECDH_compute_key(shared, ECDH_SIZE, point2c, ecdh, NULL))) handleErrors();
	printf("len=%d\n",len);
	disp("shared", shared, len);
 
	/* bob */
	//ComputeKey
	pointc = EC_POINT_new(group2);
	EC_POINT_oct2point(group2, pointc, pubkey, ECDH_SIZE, NULL);
 
	if (0 != EC_POINT_cmp(group2, point, pointc, NULL)) handleErrors();
	if(0 == (len2 = ECDH_compute_key(shared2, ECDH_SIZE, pointc, ecdh2, NULL))) handleErrors();
	printf("len2=%d\n",len2);
	disp("shared2", shared2, len2);
 
	/* alice */
	EC_POINT_free(pointc);
	EC_KEY_free(ecdh);
	/* bob */
	EC_POINT_free(point2c);
	EC_KEY_free(ecdh2);
 
	printf("To the end\n");

	//sm2 
	EC_KEY* sm2key;
	EC_KEY* key = NULL;
    BN_CTX *ctx = NULL;
    EC_GROUP* groupsm2 = NULL;
    EC_POINT* point_p = NULL;
    const EC_POINT *point_q = NULL;
    BIGNUM *p, *a, *b, *gx, *gy, *z;
	EC_POINT* pub_key = NULL;

    p = BN_new();  
    a = BN_new();  
    b = BN_new();  

    gx = BN_new();
    gy = BN_new();
    z = BN_new();

    //初始化一个空算法组
    groupsm2 = EC_GROUP_new(EC_GFp_mont_method());  

    //将国密算法的参数转为大数
    BN_hex2bn(&p, _P);  
    BN_hex2bn(&a, _a);  
    BN_hex2bn(&b, _b);
    BN_hex2bn(&gx, _Gx);
    BN_hex2bn(&gy, _Gy);
    BN_hex2bn(&z, _n); //素数P的阶

    ctx = BN_CTX_new();

    //先确定sm2曲线
    //传入a，b参数
    if (!EC_GROUP_set_curve_GFp(groupsm2, p, a, b,ctx))  
    {  
        goto err_process;  
    }  

    //取曲线上的三个点
    point_p = EC_POINT_new(groupsm2);   

    //设置基点坐标
    if (!EC_POINT_set_affine_coordinates_GFp(groupsm2, point_p, gx, gy, ctx))
    {
        goto err_process;
    }
    //
    ////确定P点事否在曲线上
    if (!EC_POINT_is_on_curve(groupsm2, point_p, ctx))
    {
        goto err_process;
    }

    //设置椭圆曲线的基G，完成了国密曲线
    if(!EC_GROUP_set_generator(groupsm2, point_p, z, BN_value_one()))  
    {  
        goto err_process;  
    }  

    //生成国密Key
    key = EC_KEY_new();
    if (!EC_KEY_set_group(key, groupsm2))
    {
        goto err_process;
    }

    if(!EC_KEY_generate_key(key))
    {
        goto err_process;
    }

    printf("gen key success:\n the prv is %s\n", 
        BN_bn2hex(EC_KEY_get0_private_key(key)));

	pub_key = EC_POINT_new(groupsm2); 
	if (pub_key == NULL){ 
         goto err_process; 
    } 
	if(!EC_POINT_mul(groupsm2, pub_key, EC_KEY_get0_private_key(key), NULL, NULL, ctx)) 
     	goto err_process; 

	EC_POINT_get_affine_coordinates_GFp(groupsm2, pub_key, gx, gy , NULL);
	printf("gen key success:\n the pub is:\ngx: %s\ngy: %s\n", 
         BN_bn2hex(gx), BN_bn2hex(gy));

    point_q = EC_KEY_get0_public_key(key);
	if(!EC_POINT_get_affine_coordinates_GFp(groupsm2, point_q, gx, gy , NULL))
		goto err_process;
	printf("gen key success:\n the pub is:\ngx: %s\ngy: %s\n", 
        BN_bn2hex(gx), BN_bn2hex(gy));

err_process:

    if (point_p != NULL)
    {
        EC_POINT_free(point_p);
    }

    if (groupsm2 != NULL)
    {
        EC_GROUP_free(groupsm2);
    }

    if (ctx != NULL)
    {
        BN_CTX_free(ctx);
    }

    if (key != NULL)
    {
        EC_KEY_free(key);
    }


    printf("hello world %s\n", ssl_version);
}