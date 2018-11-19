/*! @file flight-control/main.cpp
 *  @version 3.3
 *  @date Jun 05 2017
 *
 *  @brief
 *  main for Flight Control API usage in a Linux environment.
 *  Provides a number of helpful additions to core API calls,
 *  especially for position control, attitude control, takeoff,
 *  landing.
 *
 *  @Copyright (c) 2016-2017 DJI
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "flight_control_sample.hpp"

using namespace DJI::OSDK;
using namespace DJI::OSDK::Telemetry;
void TakeOff(Vehicle *vehicle){
	monitoredTakeoff(vehicle);
	moveByPositionOffset(vehicle, 0, 0, 6, 0);
}
void Landing(Vehicle *vehicle){
	monitoredTakeoff(vehicle);
	moveByPositionOffset(vehicle, 0, 0, 6, 0);
}
void MoveForward(Vehicle *vehicle,float x){
	moveByPositionOffset(vehicle, x, 0, 0, 0);
}
void MoveBack(Vehicle *vehicle,float x){
	moveByPositionOffset(vehicle, -x, 0, 0, 0);
}
void MoveUp(Vehicle *vehicle,float z){
	moveByPositionOffset(vehicle, 0, 0, -z, 0);
}
void MoveDown(Vehicle *vehicle,float z){
	moveByPositionOffset(vehicle, 0, 0, z, 0);
}
void MoveLeft(Vehicle *vehicle,float y){
	moveByPositionOffset(vehicle, 0, -y, 0, 0);
}
void MoveRight(Vehicle *vehicle,float y){
	moveByPositionOffset(vehicle, 0, y, 0, 0);
}
void TurnLeft(Vehicle *vehicle,float yew){
	moveByPositionOffset(vehicle, 0, 0, 0, -yew);
}
void TurnRight(Vehicle *vehicle,float yew){
	moveByPositionOffset(vehicle, 0, 0, 0, yew);
}

typedef void (*ACTION)(Vehicle *,float);

typedef struct{
	const char *cmd;
	ACTION act;
}CMD_MATCH;

CMD_MATCH cmd[] = {
		{"TakeOff", TakeOff},
		{"Landing", Landing},
		{"MoveForward", MoveForward},
		{"MoveBack", MoveBack},
		{"MoveLeft", MoveLeft},
		{"MoveRight", MoveRight},
		{"MoveUp", MoveUp},
		{"MoveDown", MoveDown},
		{"TurnLeft", TurnLeft},
		{"TurnRight", TurnRight}
};

void DronAction(Vehicle *vehicle, const char* cmds, float x){
	int i = 0;
	for(i = 0; i<10 ; i++){
		if(strstr(cmd[i].cmd, cmds)){
			cmd[i].act(vehicle, x);
		}
	}
}

int receiveCmd(Vehicle *vehicle)
{
    int server_sockfd;
    int len;
    struct sockaddr_in my_addr;
    struct sockaddr_in remote_addr;
    socklen_t sin_size;
    char buf[BUFSIZ];
    memset(&my_addr,0,sizeof(my_addr));
    my_addr.sin_family=AF_INET; //设置为IP通信
    my_addr.sin_addr.s_addr=INADDR_ANY;//自动获取本机IP
    my_addr.sin_port=htons(8000);

    /*IPv4协议，面向无连接通信，UDP协议*/
    if((server_sockfd=socket(PF_INET,SOCK_DGRAM,0))<0)
    {
        perror("socket");
        return 1;
    }

    if (bind(server_sockfd,(struct sockaddr *)&my_addr,sizeof(struct sockaddr))<0)
    {
        perror("bind");
        return 1;
    }
    sin_size=sizeof(struct sockaddr_in);
    printf("waiting for a packet...\n");

    while(1){
		/*接收客户端的数据并将其发送给客户端--recvfrom是无连接的*/
		if((len=recvfrom(server_sockfd,buf,BUFSIZ,0,(struct sockaddr *)&remote_addr,&sin_size))<0)
		{
			perror("recvfrom");
			return 1;
		}
		printf("received packet from %s:\n",inet_ntoa(remote_addr.sin_addr));
		buf[len]='\0';
		printf("contents: %s\n",buf);
		DronAction(vehicle, buf, 6);
    }

    // if(buf == ""){
    //    cmd process
	// }
    return 0;
}


/*! main
 *
 */
int
main(int argc, char** argv)
{
  // Initialize variables
  int functionTimeout = 1;
  // Setup OSDK.
  LinuxSetup linuxEnvironment(argc, argv);
  Vehicle*   vehicle = linuxEnvironment.getVehicle();
  if (vehicle == NULL)
  {
    std::cout << "Vehicle not initialized, exiting.\n";
    return -1;
  }

  // Obtain Control Authority
  vehicle->obtainCtrlAuthority(functionTimeout);

  receiveCmd(vehicle);
  printf("recving......\n");

//  // Display interactive prompt
//  std::cout
//    << "| Available commands:                                            |"
//    << std::endl;
//  std::cout
//    << "| [a] Monitored Takeoff + Landing                                |"
//    << std::endl;
//  std::cout
//    << "| [b] Monitored Takeoff + Position Control + Landing             |"
//    << std::endl;
//  char inputChar;
//  std::cin >> inputChar;
//
//
//  switch (inputChar)
//  {
//    case 'a':
//      monitoredTakeoff(vehicle);
//      monitoredLanding(vehicle);
//      break;
//    case 'b':
//      monitoredTakeoff(vehicle);
//      moveByPositionOffset(vehicle, 0, 6, 6, 30);
//      moveByPositionOffset(vehicle, 6, 0, -3, -30);
//      moveByPositionOffset(vehicle, -6, -6, 0, 0);
//      monitoredLanding(vehicle);
//      break;
//    default:
//      break;
//  }

  return 0;
}
