#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <map>
using namespace std;

// ========================
//       USER CLASS
// ========================
class User {
private:
    string username;
    string password;
    string phoneNumber;
    string status;
    string lastSeen;

public:
    User() {
        // TODO: Implement default constructor
    }
    
    User(string uname, string pwd, string phone) {
        // TODO: Implement parameterized constructor
    }
    
    string getUsername() const {
        // TODO: Implement getter
        return "";
    }
    
    string getPhoneNumber() const {
        // TODO: Implement getter
        return "";
    }
    
    string getStatus() const {
        // TODO: Implement getter
        return "";
    }
    
    string getLastSeen() const {
        // TODO: Implement getter
        return "";
    }
    
    void setStatus(string newStatus) {
        // TODO: Implement setter
    }
    
    void setPhoneNumber(string phone) {
        // TODO: Implement setter
    }
    
    void updateLastSeen() {
        // TODO: Implement last seen update
    }
    
    bool checkPassword(string pwd) const {
        // TODO: Implement password check
        return false;
    }
    
    void changePassword(string newPwd) {
        // TODO: Implement password change
    }
};

// ========================
//      MESSAGE CLASS
// ========================
class Message {
private:
    string sender;
    string content;
    string timestamp;
    string status;
    Message* replyTo;
    map<string,string> emojis;

    
public:
    Message() {
        // TODO: Implement default constructor
        sender = "";
        content="";
        timestamp = "";
        status = "sent";
        replyTo = nullptr;

    }
    
    Message(string sndr, string cntnt) {
        // TODO: Implement parameterized constructor
        sender = sndr;
        content = cntnt;
        time_t now = time(0);
        timestamp = ctime(&now);
        status = "sent";
        replyTo = nullptr;
    }
    
    string getContent() const {
        // TODO: Implement getter
        return content;
    }
    
    string getSender() const {
        // TODO: Implement getter
        return sender;
    }
    
    string getTimestamp() const {
        // TODO: Implement getter
        return timestamp;
    }
    
    string getStatus() const {
        // TODO: Implement getter
        return status;
    }
    
    Message* getReplyTo() const {
        // TODO: Implement getter
        return replyTo;
    }
    
    void setStatus(string newStatus) {
        status = newStatus;
    }
    
    void setReplyTo(Message* msg) {
        // TODO: Implement setter
        replyTo = msg;
    }
    
    void updateTimestamp() {
        // TODO: Implement timestamp update
        time_t now = time(0);
        timestamp = ctime(&now);
    }
    
    void display() const {
        // TODO: Implement message display
        cout << "Sender: " << sender << endl;
        cout << "Message: " << content << endl;
        cout <<  timestamp << endl;
    }
    
    void addEmoji(string emojiCode) {

        emojis[":)"] = "😊";
        emojis[":("] = "☹️";
        emojis[":D"] = "😄";
        emojis["<3"] = "❤️";

        if(emojis.count(emojiCode))
            content += emojis[emojiCode];
        else
            content += emojiCode;

    }
};

// ========================
//       CHAT CLASS (BASE)
// ========================
class Chat {
protected:
    vector<string> participants;
    vector<Message> messages;
    string chatName;
    
public:
    Chat() {
        // TODO: Implement default constructor
    }
    
    Chat(vector<string> users, string name) {
        // TODO: Implement parameterized constructor
    }
    
    void addMessage(const Message& msg) {
        // TODO: Implement message addition
    }
    
    bool deleteMessage(int index, const string& username) {
        // TODO: Implement message deletion
        return false;
    }
    
    virtual void displayChat() const {
        // TODO: Implement chat display
    }
    
    vector<Message> searchMessages(string keyword) const {
        // TODO: Implement message search
        return {};
    }
    
    void exportToFile(const string& filename) const {
        // TODO: Implement export to file
    }
};

// ========================
//     PRIVATE CHAT CLASS
// ========================
class PrivateChat : public Chat {
private:
    string user1;
    string user2;
    
public:
    PrivateChat(string u1, string u2) {
        // TODO: Implement constructor
    }
    
    void displayChat() const override {
        // TODO: Implement private chat display
    }
    
    void showTypingIndicator(const string& username) const {
        // TODO: Implement typing indicator
    }
};

// ========================
//      GROUP CHAT CLASS
// ========================
class GroupChat : public Chat {
private:
    vector<string> admins;
    string description;
    
public:
    GroupChat(vector<string> users, string name, string creator) {
        // TODO: Implement constructor
    }
    
    void addAdmin(string newAdmin) {
        // TODO: Implement add admin
    }
    
    bool removeParticipant(const string& admin, const string& userToRemove) {
        // TODO: Implement remove participant
        return false;
    }
    
    bool isAdmin(string username) const {
        // TODO: Implement admin check
        return false;
    }
    
    bool isParticipant(string username) const {
        // TODO: Implement participant check
        return false;
    }
    
    void setDescription(string desc) {
        // TODO: Implement set description
    }
    
    void displayChat() const override {
        // TODO: Implement group chat display
    }
    
    void sendJoinRequest(const string& username) {
        // TODO: Implement join request
    }
};

// ========================
//    WHATSAPP APP CLASS
// ========================
class WhatsApp {
private:
    vector<User> users;
    vector<Chat*> chats;
    int currentUserIndex;
    
    int findUserIndex(string username) const {
        for(int r = 0; r < users.size(); r++)
            if(users[r].username = username)
                return users[r].index;
        // TODO: Improve user search
        return -1;
    }
    
    bool isLoggedIn() const {
        return currentUserIndex != -1;
    }
    
    string getCurrentUsername() const {
        return users[currentUserIndex].username;
    }
    
public:
    WhatsApp() : currentUserIndex(-1) {}
    
    void signUp() {
        string new_username;
        string new_password;
        string new_phonenumber;
        bool unique_new_username;
        bool unique_new_phonenumber;
        bool reasonable_new_password;
        
        cout << "You have chosen to sign up\n";

        do {
            cout << "Pick a username that hasn't been picked before: \n";
            cin >> new_username;
            unique_new_username = findUserIndex(new_username) == -1 ? false : true;
        } while (!unique_new_username);

        do {
            cout << "Enter a phone number that hasn't been picked before: \n";
            cin >> new_phonenumber;
            unique_new_phonenumber = true;
            for(User u : users){
                if(u.phoneNumber == new_phonenumber){
                    unique_new_phonenumber = false;
                    break;
                }
            }
        } while (!unique_new_phonenumber);

        
        do {
            cout << "Enter a reasonable password\n";
            cin >> new_password;
            reasonable_new_password = true;
            if(new_password == "")
                reasonable_new_password = false;
            
        } while (!reasonable_new_password);
        
        users.push_back(User(new_username, new_password, new_phonenumber));
        cout << "You are now registered\n";
    }
    
    void login() {
        if(isLoggedIn()){
            cout << "You are already logged in.\n";
            return;
        }

        string entered_username;
        string entered_password;
        int potential_user_index;
        
        cout << "You have chosen to log in\n";
        
        do{
            cout << "Enter your username\n";
            cin >> entered_username;
            potential_user_index = findUserIndex(entered_username);
        }while(potential_user_index == -1);
        
        do{
            cout << "Enter your password\n";
            cin >> entered_password;
        }while(entered_password != users[potential_user_index]);
        
        currentUserIndex = potential_user_index;
    }
    
    void startPrivateChat() {
        string second_username;
        int second_username_index;
        cout << "You have chosen to start a private chat.\n";
        
        do{
            cout << "Enter the username of the person you want to privately chat with.\n";
            cin >> second_username;
            second_username_index = findUserIndex(second_username);
        }
        while(second_username_index == -1);
        
        new_private_chat = PrivateChat(getCurrentUsername(), second_username);
        new_private_chat.display();
    }
    
    void createGroup() {
        vector<string> participants;
        cout << "You have chosen to create a group\n";
        string potential_user;
        string group_name;
        cout << "Enter the usernames of the people you'd like to add:\n";
        cout << "When you're done, type \"-1\"\n\n";

        do{
            cout << "Enter a username\n";
            cin >> potential_user;
            if(findUserIndex(potential_user) == -1){
                cout << "That user doesn't exist\n";
            }
            else{
                participants.push_back(potential_user)
            }

        }while(potential_user != "-1");

        cout << "Pick a name for the group\n";
        cin >> group_name;

        GroupChat new_groupchat = GroupChat(participants,group_name,currentUserIndex);
        new_groupchat.display();
    }
    
    void viewChats() const {
        
        for(chat* c : chats){
            cout << "The chat called: " + chatName << endl;
            cout << "Its participants are: \n";
            for(string part : c->participants){
                cout << part << endl;
            }
            cout << "Here is each message along with who sent it\n";
            cout << "and when it was sent.\n"
            for(Message msg : messages){
                cout << msg.sender << " said: " << msg.content << endl;
                cout << msg.timestamp << endl;
            }   
        }
    }
    
    void logout() {
        currentUserIndex = -1;
    }
    
    void run() {
        while (true) {
            if (!isLoggedIn()) {
                cout << "\n1. Login\n2. Sign Up\n3. Exit\nChoice: ";
                int choice;
                cin >> choice;
                
                if (choice == 1) login();
                else if (choice == 2) signUp();
                else if (choice == 3) break;
            }
            else {
                cout << "\n1. Start Private Chat\n2. Create Group\n3. View Chats\n4. Logout\nChoice: ";
                int choice;
                cin >> choice;
                
                if (choice == 1) startPrivateChat();
                else if (choice == 2) createGroup();
                else if (choice == 3) viewChats();
                else if (choice == 4) logout();
            }
        }
    }
};

// ========================
//          MAIN
// ========================
int main() {
    WhatsApp whatsapp;
    whatsapp.run();
    return 0;
}