#For mongoDB for accounts
from pymongo.mongo_client import MongoClient
from pymongo.server_api import ServerApi

uri = "mongodb+srv://HaltingUltraman:Scoutuser2728%40@userscluster.iinvp.mongodb.net/?retryWrites=true&w=majority&appName=UsersCluster"

# Create a new client and connect to the server
client = MongoClient(uri)

# Send a ping to confirm a successful connection
try:
    client.admin.command('ping')
    print("Pinged your deployment. You successfully connected to MongoDB!")
except Exception as e:
    print(e)

#For flask for HTML and Python interchangeability
from flask import Flask, render_template, request

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def index():
    if request.method == 'POST':
        # Get data from the form
        Email = request.form['Email']
        Password = request.form['Password']
    
    return render_template(Email)

if __name__ == '__main__':
    app.run(debug=True)

#Data from mongodb
database = client['UsersCluster']
collection = database['UserDB']

signedIn = False

#Requests sign in or log in
signIn = input("S to sign up or L to log in: ")
while signIn != "S" and signIn != "L":
    signIn = input("S to sign up or L to log in: ")

#Sign up
if signIn == "S":
    #User must input sign-up account details
    newEmail = input("Type in your email ")
    newPassword = input("Type in your password ")
    newPasswordConfirmation = input("Confirm your password ")

    #Checks if password and confirming password match
    while newPassword != newPasswordConfirmation:
        newPasswordConfirmation = input("Passwords do not match. Please reconfirm your password. ")

    #Form new account
    newAccount = {"Email" : newEmail,
                  "Password" : newPassword,
    }

    collection.insert_one(newAccount)
    print("New account has been created!")
    

#Login
if signIn == "L":
    while signedIn == False:
        #Searches for email and password
        loginEmail = input("Type in your email ")
        loginPassword = input("Type in your password ")

        #Test checking for email
        result = collection.find_one({"Email": loginEmail, "Password" : loginPassword})
        if result != None:
            print("Logged in. Hooray!")
            signedIn = True
        else:
            print("Email or password are incorrect. Please try again.")

#Update login info
changeInfo = input("Y to change information ")
if changeInfo == "Y":
    #Type of information being changed
    changeType = input("E to change Email, P to change Password ")
    while changeType != "E" and changeType != "P":
        changeType = input("E to change Email, P to change Password ")

    #Change email
    if changeType == "E":
        newEmail = input("Your new Email: ")
        oldEmail = {"Email" : loginEmail}
        emailUpdate = {"$set" : {"Email" : newEmail}}
        collection.update_one(oldEmail, emailUpdate)

    #Change password
    if changeType == "P":
        newerPassword = input("Your new Password: ")
        oldPassword = {"Password" : loginPassword}
        passwordUpdate = {"$set": {"Password" : newEmail}}
        collection.update_one(oldPassword, passwordUpdate)
