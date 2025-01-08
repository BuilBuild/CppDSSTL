<!--
 * @Author: LeiJiulong
 * @Date: 2024-12-31 16:38:32
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2024-12-31 16:48:29
 * @Description: 
-->
# Mysql数据库表设置
## 相关设置
- 开发包
    ```shell
    sudo apt-get install libmysqlclient-dev
    ```
- 字符集设置
    ```shell
    mysql>set character_set_server=utf8;
    ```
## 库表创建
- 库名
    ```sql
    create database chat;
    use chat;
    
    ```