import smtplib
from email.message import EmailMessage
import os
from dotenv import load_dotenv

load_dotenv()  # load all env variables

def email_alert(subject, body, to):
    msg = EmailMessage()
    msg.set_content(body)
    msg['subject'] = subject
    msg['to'] = to


    user = os.environ.getenv("EMAIL_USER")  # get email user
    msg["from"] = user
    password = os.environ.getenv("EMAIL_USER_PASSWORD")  # get email user's password 

    server = smtplib.SMTP("smtp.gmail.com", 587)
    server.starttls()
    server.login(user, password)
    server.send_message(msg)
    server.quit()

if __name__ == "__main__":
    email_alert("Hey subject", "Hello World Body", "manuelamanetjr@gmail.com")
