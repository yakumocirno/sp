import requests
from bs4 import BeautifulSoup
import threading
import sqlite3
from database import create_connection, insert_data, update_data

class Crawler(threading.Thread):
    def __init__(self, url, db_file):
        threading.Thread.__init__(self)
        self.url = url
        self.db_file = db_file

    def run(self):
        try:
            response = requests.get(self.url)
            response.raise_for_status()
            soup = BeautifulSoup(response.text, 'html.parser')
            title = soup.title.string if soup.title else 'No title'
            self.save_to_db(self.url, title)
        except requests.RequestException as e:
            print(f"Error fetching {self.url}: {e}")

    def save_to_db(self, url, title):
        db_conn = create_connection(self.db_file)
        with db_conn:
            insert_data(db_conn, url, title)

def main():
    db_file = 'crawler.db'
    db_conn = create_connection(db_file)
    
    # 更新數據示例
    updated_title = 'Updated Title'
    update_data(db_conn, 1, updated_title)  # 假設要更新 id 為 1 的記錄

    urls = [
        'https://news.ycombinator.com/',
        'https://www.facebook.com/',
        'https://www.youtube.com/',
        'https://www.twitch.tv/'
        
    ]

    threads = []
    for url in urls:
        thread = Crawler(url, db_file)
        thread.start()
        threads.append(thread)

    for thread in threads:
        thread.join()

if __name__ == "__main__":
    main()