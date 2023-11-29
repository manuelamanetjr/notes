import smtplib
from email.message import EmailMessage

def email_alert(subject, body, to):
    msg = EmailMessage()
    msg.set_content(body)
    msg['subject'] = subject
    msg['to'] = to


    user = "smsalertprac@gmail.com"
    msg["from"] = user
    password = "nuescnvuiwlhhlqi"

    server = smtplib.SMTP("smtp.gmail.com", 587)
    server.starttls()
    server.login(user, password)
    server.send_message(msg)
    server.quit()

if __name__ == "__main__":
    email_alert("Hey subject", "Hello World Body", "manuelamanetjr@gmail.com")