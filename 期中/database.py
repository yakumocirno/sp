import sqlite3
from sqlite3 import Error

def create_connection(db_file):
    conn = None
    try:
        conn = sqlite3.connect(db_file, check_same_thread=False)
        create_table(conn)
    except Error as e:
        print(e)
    return conn

def create_table(conn):
    try:
        sql_create_projects_table = """CREATE TABLE IF NOT EXISTS crawled_data (
                                        id integer PRIMARY KEY,
                                        url text NOT NULL,
                                        title text
                                    );"""
        c = conn.cursor()
        c.execute(sql_create_projects_table)
    except Error as e:
        print(e)

def insert_data(conn, url, title):
    sql = ''' INSERT INTO crawled_data(url, title)
              VALUES(?,?) '''
    cur = conn.cursor()
    cur.execute(sql, (url, title))
    conn.commit()
    return cur.lastrowid

def update_data(conn, id, new_title):
    sql = ''' UPDATE crawled_data
              SET title = ?
              WHERE id = ?'''
    cur = conn.cursor()
    cur.execute(sql, (new_title, id))
    conn.commit()