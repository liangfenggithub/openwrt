#include "mqtt_nossl.h"


bool session = true;
void my_message_callback(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message)
{
    if(message->payloadlen)
    {
        printf("%s %s", message->topic, message->payload);
    }
    else
    {
        printf("%s (null)\n", message->topic);
    }
    fflush(stdout);
}
void my_connect_callback(struct mosquitto *mosq, void *userdata, int result)
{
    int i;
    if(!result)
    {
        /* Subscribe to broker information topics on successful connect. */
        mosquitto_subscribe(mosq, NULL, "topic/qos0", 2);
    }
    else
    {
        fprintf(stderr, "Connect failed\n");
    }
}
void my_subscribe_callback(struct mosquitto *mosq, void *userdata, int mid, int qos_count, const int *granted_qos)
{
    int i;
    printf("Subscribed (mid: %d): %d", mid, granted_qos[0]);
    for(i=1; i<qos_count; i++)
    {
        printf(", %d", granted_qos[i]);
    }
    printf("\n");
}
void my_log_callback(struct mosquitto *mosq, void *userdata, int level, const char *str)
{
    /* Pring all log messages regardless of level. */ 
    printf("log:%s\n", str);
}
int main(int argc, char *argv[])
{
    char buff[MSG_MAX_SIZE];
    struct mosquitto *mosq = NULL; 
	char tcp_server_port[256];
	char tcp_server_ip[256];
    printf("enter main\r\n");

	if (argc >= 2){
		if (strcmp(argv[1],"-v") == 0){
			printf("mqtt_nossl v1.0\n");
			return 0;
		}else if (strcmp(argv[1],"-h") == 0){
			printf("-v for version\n");
			printf("-h for help\n");
			printf("mqtt_test <IP> <port>\n");
			return 0;
		}else if (strcmp(argv[1], "mqtt_test") == 0){
            //get ip and port            
			strcpy(tcp_server_ip, argv[2]);
			strcpy(tcp_server_port, argv[3]);

            //libmosquitto 库初始化
            mosquitto_lib_init(); 
            //创建mosquitto客户端
            mosq = mosquitto_new(NULL,session,NULL);
            if(!mosq)
            {
                printf("create client failed..\n");
                mosquitto_lib_cleanup();
                return 1;
            }
            //设置回调函数，需要时可使用
            mosquitto_log_callback_set(mosq, my_log_callback);
            mosquitto_connect_callback_set(mosq, my_connect_callback);
            mosquitto_message_callback_set(mosq, my_message_callback);
            mosquitto_subscribe_callback_set(mosq, my_subscribe_callback);
            //客户端连接服务器
            if(mosquitto_connect(mosq, tcp_server_ip, (unsigned short)atoi(tcp_server_port), KEEP_ALIVE))
            {
                fprintf(stderr, "Unable to connect.\n");
                return 1;
            }
            //循环处理网络消息
            //mosquitto_loop_forever(mosq, -1, 1);
            
            //开启一个线程，在线程里不停的调用 mosquitto_loop() 来处理网络信息
            int loop = mosquitto_loop_start(mosq);
            if(loop != MOSQ_ERR_SUCCESS)
            {
                printf("mosquitto loop error\n");
                return 1;
            }
            while(fgets(buff, MSG_MAX_SIZE, stdin) != NULL)
            {
                /*发布消息*/
                mosquitto_publish(mosq,NULL,"topic/qos1",strlen(buff)+1,buff,0,0);
                memset(buff,0,sizeof(buff));
            }

            mosquitto_destroy(mosq);
            mosquitto_lib_cleanup();

		}else{
			printf("Unknown argument %s\n",argv[1]);
			return -1;
		}
	}

    return 0;
}

