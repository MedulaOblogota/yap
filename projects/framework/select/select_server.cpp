void StdInput(int udp_port_num, int tcp_port_num, int broadcast_port_num)
{
    pthread_t thread[3];
	int udp_port_num1, tcp_port_num1, broadcast_port_num1;

	pthread_create(&thread[0], NULL, CreateUDPServer, &udp_port_num);
	pthread_create(&thread[1], NULL, CreateTCPServer, &tcp_port_num);
	pthread_create(&thread[2], NULL, CreateBroadcastServer, &broadcast_port_num);

	pthread_join(thread[0], NULL);
	pthread_join(thread[1], NULL);
	pthread_join(thread[2], NULL);
}

