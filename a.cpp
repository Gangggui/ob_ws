/*******************************************************************
 *	Copyright(c) 2006-2022 Novasky
 *  All rights reserved.
 *
 *	文件名称: video_task.cpp
 *	简要描述:
 *
 *	当前版本:0.1
 *	作者: Ganggui Qu
 *	日期: 2022/6/28 下午5:08
 *	说明:
 ******************************************************************/
#include "vector"
#include "iostream"
#include "queue"
#include "hv/TcpServer.h"
#include "hv/TcpClient.h"
#include "hv/htime.h"
#include "hv/hloop.h"

#include "logger.h"
#include "spin_lock.hpp"
#include "json.hpp"

#define debug 1
using  namespace hv;

#define FTP_TASK_PORT 9051

int main() {

//    signal(SIGINT, network_ptr->sig_handler);
    EventLoopPtr loop(new EventLoop);
    std::shared_ptr<TcpServer> srv = std::make_shared<TcpServer>(loop);
    int listenfd = srv->createsocket(FTP_TASK_PORT);
    if (listenfd < 0) {
        return -20;
    }
    srv->onConnection = [](const SocketChannelPtr& channel) {
        std::string peeraddr = channel->peeraddr();
        if (channel->isConnected()) {
            printf("%s connected! connfd=%d id=%d tid=%ld\n", peeraddr.c_str(), channel->fd(), channel->id(), currentThreadEventLoop->tid());
        } else {
            printf("%s disconnected! connfd=%d id=%d tid=%ld\n", peeraddr.c_str(), channel->fd(), channel->id(), currentThreadEventLoop->tid());
        }
    };
    srv->onMessage = [&srv](const SocketChannelPtr& channel, Buffer* buf) {
        // echo
        std::string msg((char*)buf->data(), static_cast<std::size_t>((int)buf->size()));

        srv->broadcast(msg);
    };
    // 加入拆包解包机制：对应安卓协议：前两位为帧头，第3-4位为长度，小字节在前
    /*
     * 测试用例：先后发送两条
     * 10 01 02 00 01 02 03
     * 04 02 00 01 02
     * 接收结果：
        [2022-7-13 19:06:48】
        10 1 2 0 1 2
        [2022-7-13 19:06:57】
        3 4 2 0 1 2
        */
    unpack_setting_t protorpc_unpack_setting;
    memset(&protorpc_unpack_setting, 0, sizeof(unpack_setting_t));
    protorpc_unpack_setting.mode = UNPACK_BY_LENGTH_FIELD;
    protorpc_unpack_setting.package_max_length = DEFAULT_PACKAGE_MAX_LENGTH;
    protorpc_unpack_setting.body_offset = 4;
    protorpc_unpack_setting.length_field_offset = 2;
    protorpc_unpack_setting.length_field_bytes = 2;
    protorpc_unpack_setting.length_field_coding = ENCODE_BY_LITTEL_ENDIAN;
    srv->setUnpack(&protorpc_unpack_setting);
    srv->start();

    loop->run();

    return 0;
}
