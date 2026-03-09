#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <map>
using namespace std;

// ========================
//     ASSISSTING FUNCTIONS
// ========================
bool inList(const vector<string> &v, const string &s)
{
    for (int i = 0; i < (int)v.size(); i++)
        if (v[i] == s)
            return true;
    return false;
}

void removeFrom(vector<string> &v, const string &s)
{
    for (int i = 0; i < (int)v.size(); i++)
        if (v[i] == s)
        {
            v.erase(v.begin() + i);
            return;
        }
}

// ========================
//       USER CLASS
// ========================
class User
{
public:
    string username;
    string password;
    string phoneNumber;
    string status;
    string lastSeen;

    User()
    {
        username = "";
        password = "";
        phoneNumber = "";
        status = "Offline";
        updateLastSeen();
    }

    User(const string &uName, const string &pwd, const string &phone)
    {
        username = uName;
        phoneNumber = phone;
        status = "Online";

        if (pwd.length() >= 6)
        {
            password = pwd;
        }
        else
        {
            cout << "Error: Password must be at least 6 characters.\n";
            password = "";
        }
        updateLastSeen();
    }

    string getUsername() const { return username; }
    string getPhoneNumber() const { return phoneNumber; }
    string getStatus() const { return status; }
    string getLastSeen() const { return lastSeen; }

    void setStatus(const string &newStatus)
    {
        status = newStatus;
        updateLastSeen();
    }

    void setPhoneNumber(const string &phone)
    {
        phoneNumber = phone;
        updateLastSeen();
    }

    void updateLastSeen()
    {
        time_t now = time(0);
        string timeStr = ctime(&now);
        if (!timeStr.empty() && timeStr.back() == '\n')
            timeStr.pop_back();
        lastSeen = timeStr;
    }

    bool checkPassword(const string &pwd) const
    {
        return password == pwd;
    }

    void changePassword(const string &newPwd)
    {
        if (newPwd.length() >= 6)
        {
            password = newPwd;
            updateLastSeen();
            cout << "Password updated successfully!\n";
        }
        else
        {
            cout << "Error: New password is too short.\n";
        }
    }
};

// ========================
//      MESSAGE CLASS
// ========================
class Message
{
public:
    string sender;
    string content;
    string timestamp;
    string status;
    Message *replyTo;
    map<string, string> emojis;

    Message()
    {
        sender = "";
        content = "";
        timestamp = "";
        status = "sent";
        replyTo = nullptr;
    }

    Message(string sndr, string cntnt)
    {
        sender = sndr;
        content = cntnt;
        time_t now = time(0);
        timestamp = ctime(&now);
        status = "sent";
        replyTo = nullptr;
    }

    string getContent() const { return content; }
    string getSender() const { return sender; }
    string getTimestamp() const { return timestamp; }
    string getStatus() const { return status; }
    Message *getReplyTo() const { return replyTo; }

    void setStatus(string newStatus) { status = newStatus; }

    void setReplyTo(Message *msg) { replyTo = msg; }

    void updateTimestamp()
    {
        time_t now = time(0);
        timestamp = ctime(&now);
    }

    void display() const
    {
        cout << "Sender: " << sender << endl;
        cout << "Message: " << content << endl;
        cout << "Time: " << timestamp << endl;
        cout << "Status: " << status << endl;
    }

    void addEmoji(string emojiCode)
    {
        emojis[":)"] = "😊";
        emojis[":("] = "☹️";
        emojis[":D"] = "😄";
        emojis["<3"] = "❤️";

        if (emojis.count(emojiCode))
            content += emojis[emojiCode];
        else
            content += emojiCode;
    }
};

// ========================
//       CHAT CLASS
// ========================
class Chat
{
public:
    vector<string> participants;
    vector<Message> messages;
    string name;

    Chat() : name(""), participants({}), messages({}) {}
    Chat(vector<string> p, string n)
    {
        participants = p;
        name = n;
    }
    virtual ~Chat() {}

    bool hasUser(string u) { return inList(participants, u); }

    void addMessage(Message m)
    {
        messages.push_back(m);
        for (int i = 0; i < (int)messages.size() - 1; i++)
            if (messages[i].status == "sent")
                messages[i].status = "delivered";
    }

    bool deleteMessage(int i, string user)
    {
        if (i < 0 || i >= (int)messages.size())
        {
            cout << "Invalid index.\n";
            return false;
        }
        if (messages[i].sender != user)
        {
            cout << "Not your message.\n";
            return false;
        }
        messages.erase(messages.begin() + i);
        cout << "Deleted.\n";
        return true;
    }

    virtual void display()
    {
        cout << "\n--- " << name << " ---\n";
        if (messages.empty())
            cout << "(No messages)\n";
        else
            for (int i = 0; i < (int)messages.size(); i++)
                messages[i].display();
    }

    void search(string kw)
    {
        bool found = false;
        for (int i = 0; i < (int)messages.size(); i++)
            if (messages[i].content.find(kw) != string::npos)
            {
                messages[i].display();
                found = true;
            }
        if (!found)
            cout << "Not found.\n";
    }
};

// ========================
//     PRIVATE CHAT
// ========================
class PrivateChat : public Chat
{
public:
    PrivateChat(string u1, string u2) : Chat({u1, u2}, u1 + " & " + u2) {}
};

// ========================
//      GROUP CHAT
// ========================
class GroupChat : public Chat
{
public:
    vector<string> admins;
    string description;

    GroupChat(vector<string> users, string n, string creator) : Chat(users, n)
    {
        if (!inList(participants, creator))
            participants.push_back(creator);
        admins.push_back(creator);
    }

    bool isAdmin(string u) { return inList(admins, u); }

    void addAdmin(string u)
    {
        if (!inList(participants, u))
        {
            cout << "Not a member.\n";
            return;
        }
        if (!inList(admins, u))
        {
            admins.push_back(u);
            cout << u << " is now admin.\n";
        }
    }

    bool removeMember(string admin, string target)
    {
        if (!isAdmin(admin))
        {
            cout << "Admins only.\n";
            return false;
        }
        if (!inList(participants, target))
        {
            cout << "Not found.\n";
            return false;
        }
        removeFrom(participants, target);
        removeFrom(admins, target);
        cout << target << " removed.\n";
        return true;
    }

    void display() override
    {
        cout << "\n--- GROUP: " << name << " ---\n";
        if (!description.empty())
            cout << "Desc: " << description << "\n";
        cout << "Members: ";
        for (int i = 0; i < (int)participants.size(); i++)
        {
            cout << participants[i];
            if (isAdmin(participants[i]))
                cout << "[A]";
            if (i + 1 < (int)participants.size())
                cout << ", ";
        }
        cout << "\n";
        if (messages.empty())
            cout << "(No messages)\n";
        else
            for (int i = 0; i < (int)messages.size(); i++)
                messages[i].display();
    }
};

// ========================
//    WHATSAPP APP CLASS
// ========================
class WhatsApp
{
private:
    vector<User> users;
    vector<Chat *> chats;
    int currentUserIndex;

    int findUserIndex(const string &username) const
    {
        for (int r = 0; r < (int)users.size(); r++)
            if (users[r].username == username)
                return r;
        return -1;
    }

    bool isLoggedIn() const
    {
        return currentUserIndex != -1;
    }

    string getCurrentUsername() const
    {
        return users[currentUserIndex].username;
    }

public:
    WhatsApp() : currentUserIndex(-1) {}

    ~WhatsApp()
    {
        for (int i = 0; i < (int)chats.size(); i++)
            delete chats[i];
    }

    void signUp()
    {
        string new_username;
        string new_password;
        string new_phonenumber;
        bool unique_new_username;
        bool unique_new_phonenumber;
        bool reasonable_new_password;

        cout << "You have chosen to sign up\n";

        do
        {
            cout << "Pick a username that hasn't been picked before: \n";
            cin >> new_username;
            unique_new_username = (findUserIndex(new_username) == -1);
            if (!unique_new_username)
                cout << "Username already taken. Try another.\n";
        } while (!unique_new_username);

        do
        {
            cout << "Enter a phone number that hasn't been used before: \n";
            cin >> new_phonenumber;
            unique_new_phonenumber = true;
            for (const User &u : users)
            {
                if (u.phoneNumber == new_phonenumber)
                {
                    unique_new_phonenumber = false;
                    cout << "Phone number already in use. Try another.\n";
                    break;
                }
            }
        } while (!unique_new_phonenumber);

        do
        {
            cout << "Enter a password (at least 6 characters): \n";
            cin >> new_password;
            reasonable_new_password = (new_password.length() >= 6);
            if (!reasonable_new_password)
                cout << "Password too short. Must be at least 6 characters.\n";
        } while (!reasonable_new_password);

        users.push_back(User(new_username, new_password, new_phonenumber));
        cout << "You are now registered!\n";
    }

    void login()
    {
        if (isLoggedIn())
        {
            cout << "You are already logged in.\n";
            return;
        }

        string entered_username;
        string entered_password;
        int potential_user_index;

        cout << "You have chosen to log in\n";

        do
        {
            cout << "Enter your username\n";
            cin >> entered_username;
            potential_user_index = findUserIndex(entered_username);
            if (potential_user_index == -1)
                cout << "User not found.\n";
        } while (potential_user_index == -1);

        do
        {
            cout << "Enter your password\n";
            cin >> entered_password;
            if (!users[potential_user_index].checkPassword(entered_password))
                cout << "Wrong password.\n";
        } while (!users[potential_user_index].checkPassword(entered_password));

        currentUserIndex = potential_user_index;
        users[currentUserIndex].setStatus("Online");
        cout << "Logged in as " << getCurrentUsername() << "\n";
    }

    void startPrivateChat()
    {
        string second_username;
        int second_username_index;
        cout << "You have chosen to start a private chat.\n";

        do
        {
            cout << "Enter the username of the person you want to privately chat with.\n";
            cin >> second_username;
            second_username_index = findUserIndex(second_username);
            if (second_username_index == -1)
                cout << "User not found.\n";
        } while (second_username_index == -1);

        PrivateChat *new_private_chat = new PrivateChat(getCurrentUsername(), second_username);
        chats.push_back(new_private_chat);
        new_private_chat->display();
    }

    void createGroup()
    {
        vector<string> participants;
        cout << "You have chosen to create a group\n";
        string potential_user;
        string group_name;
        cout << "Enter the usernames of the people you'd like to add:\n";
        cout << "When you're done, type \"-1\"\n\n";

        do
        {
            cout << "Enter a username (or -1 to finish)\n";
            cin >> potential_user;
            if (potential_user == "-1")
                break;

            if (findUserIndex(potential_user) == -1)
            {
                cout << "That user doesn't exist\n";
            }
            else
            {
                participants.push_back(potential_user);
            }
        } while (true);

        cout << "Pick a name for the group\n";
        cin >> group_name;

        GroupChat *new_groupchat = new GroupChat(participants, group_name, getCurrentUsername());
        chats.push_back(new_groupchat);
        new_groupchat->display();
    }

    void sendMessage()
    {
        if (chats.empty())
        {
            cout << "No chats available. Start or join a chat first.\n";
            return;
        }

        cout << "Your chats:\n";
        int count = 0;
        vector<int> myChatIndices;
        for (int i = 0; i < (int)chats.size(); i++)
        {
            if (chats[i]->hasUser(getCurrentUsername()))
            {
                cout << ++count << ". " << chats[i]->name << "\n";
                myChatIndices.push_back(i);
            }
        }

        if (count == 0)
        {
            cout << "You are not part of any chat.\n";
            return;
        }

        int choice;
        cout << "Select a chat number: ";
        cin >> choice;
        if (choice < 1 || choice > count)
        {
            cout << "Invalid choice.\n";
            return;
        }

        int chatIndex = myChatIndices[choice - 1];
        string messageContent;
        cout << "Enter your message: ";
        cin.ignore();
        getline(cin, messageContent);

        Message newMsg(getCurrentUsername(), messageContent);
        chats[chatIndex]->addMessage(newMsg);
        cout << "Message sent!\n";
    }

    void viewChats() const
    {
        bool found = false;
        for (Chat *c : chats)
        {
            if (!c->hasUser(getCurrentUsername()))
                continue;

            found = true;
            cout << "\nThe chat called: " << c->name << "\n";
            cout << "Its participants are:\n";
            for (const string &part : c->participants)
                cout << "  " << part << endl;

            cout << "Messages:\n";
            if (c->messages.empty())
            {
                cout << "  (No messages)\n";
            }
            else
            {
                cout << "Here is each message along with who sent it\n";
                cout << "and when it was sent.\n";
                for (const Message &msg : c->messages)
                {
                    cout << "  " << msg.sender << " said: " << msg.content << "\n";
                    cout << "  " << msg.timestamp << "\n";
                }
            }
        }

        if (!found)
            cout << "No chats yet.\n";
    }

    void logout()
    {
        if (!isLoggedIn())
        {
            cout << "Not logged in.\n";
            return;
        }
        cout << "Goodbye, " << getCurrentUsername() << "!\n";
        users[currentUserIndex].setStatus("Offline");
        currentUserIndex = -1;
    }

    void run()
    {
        while (true)
        {
            if (!isLoggedIn())
            {
                cout << "\n1. Login\n2. Sign Up\n3. Exit\nChoice: ";
                int choice;
                cin >> choice;

                if (choice == 1)
                    login();
                else if (choice == 2)
                    signUp();
                else if (choice == 3)
                    break;
            }
            else
            {
                cout << "\n1. Start Private Chat\n2. Create Group\n3. View Chats\n4. Send Message\n5. Logout\nChoice: ";
                int choice;
                cin >> choice;

                if (choice == 1)
                    startPrivateChat();
                else if (choice == 2)
                    createGroup();
                else if (choice == 3)
                    viewChats();
                else if (choice == 4)
                    sendMessage();
                else if (choice == 5)
                    logout();
            }
        }
    }
};

void madeby()
{
    cout << "============================\n";
    cout << "        MADE BY Group 6:\n";
    cout << "============================\n";
    cout << "1) User Class       -> Shahira Abdullah\n";
    cout << "2) Message Class    -> Omar Tharwat\n";
    cout << "3) Chat Classes     -> Youssef Asaad\n";
    cout << "4) WhatsApp Class   -> Yassin Tariq\n";
    cout << "============================\n";
}

// ========================
//          MAIN
// ========================
int main()
{
    madeby();
    WhatsApp whatsapp;
    whatsapp.run();
    return 0;
}
