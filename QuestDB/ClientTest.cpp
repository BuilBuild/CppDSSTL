/*
 * @Author: LeiJiulong
 * @Date: 2025-02-12 00:51:21
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-02-12 01:06:18
 * @Description: 
 */

 // main.cpp
#include <questdb/ingress/line_sender.hpp>

int main()
{
    // auto sender = questdb::ingress::line_sender::from_conf(
    //     "http::addr=localhost:9000;username=admin;password=quest;");
    auto sender = questdb::ingress::line_sender::from_conf(
            "http::addr=101.43.5.41:9000;username=Future;password=quest;");
    questdb::ingress::line_sender_buffer buffer;
    buffer
    .table("trades")
    .symbol("symbol","ETH-USD")
    .symbol("side","sell")
    .column("price", 2615.54)
    .column("amount", 0.00044)
    .at(questdb::ingress::timestamp_nanos::now());

    // To insert more records, call `buffer.table(..)...` again.

    sender.flush(buffer);
    return 0;
}