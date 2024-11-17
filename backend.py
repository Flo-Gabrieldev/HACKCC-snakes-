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

database = client['UsersCluster']
collection = database['UserDB']

#Test creating fake email
account = "dungeonGuy@gmail.com"

signedIn = False

#Requests sign in or log in
signIn = input("S to sign up or L to log in: ")
while signIn != "S" and signIn != "L":
    signIn = input("S to sign up or L to log in: ")
    signIn = "L"

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
