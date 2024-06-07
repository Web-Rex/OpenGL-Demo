#include "../utils-lib/keys.h"


// [...] Keys
std::vector<std::function<void(int, unsigned int*)>> EVENTS::KEY_EVENTS;
std::vector<std::string> EVENTS::KEY_EVENTS_NAMES;
unsigned int EVENTS::KEYS[349] { 0 };

// [...] Mouse
std::vector<std::function<void(float, float)>> EVENTS::MOUSE_EVENTS;
std::vector<std::string> EVENTS::MOUSE_EVENTS_NAMES;



// [...] Keys
void EVENTS::Handle_Keys_Events(int key, int action)
{
    KEYS[key] = action;
    for (auto &key_events : KEY_EVENTS)
    {
        key_events(key, KEYS);
    }
}

void EVENTS::Add_Keys_Event(const std::function<void(int, unsigned int*)> &fnc, const char *str)
{
    for (auto &key_events_name : KEY_EVENTS_NAMES)
    {
        if (key_events_name == str)
        {
            std::cout << "\nERROR: [ KEYS ]\n" << "The name given to this event already exist. \n\n";
            return;
        }
    }

    KEY_EVENTS.push_back(fnc);
    KEY_EVENTS_NAMES.push_back(str);
}

void EVENTS::List_Keys_Event()
{
    std::cout << "\nKEY-EVENTS:\n";
    for (auto &key_events_name : KEY_EVENTS_NAMES)
    {
        std::cout << " -- " << key_events_name << "\n";
    }
    std::cout << "\n";
}

void EVENTS::Delete_Keys_Event(const char *str)
{
    bool not_found = true;

    for (size_t i = 0; i < KEY_EVENTS_NAMES.size(); i++)
    {
        if (KEY_EVENTS_NAMES[i] == str)
            {
                KEY_EVENTS_NAMES.erase(KEY_EVENTS_NAMES.begin() + i);
                KEY_EVENTS.erase(KEY_EVENTS.begin() + i);
                not_found = false;
            }
    }

    if (not_found == true)
        std::cout << "\nERROR: [ KEYS ]\n" << "This events name does not exist. \n\n";
}


// [...] Mouse
void EVENTS::Handle_Mouse_Events(float x_pos, float y_pos)
{
    for (auto &mouse_events : MOUSE_EVENTS)
    {
        mouse_events(x_pos, y_pos);
    }
}

void EVENTS::Add_Mouse_Event(const std::function<void (float, float)>& fnc, const char* str)
{
    for (auto &mouse_events_name : MOUSE_EVENTS_NAMES)
    {
        if (mouse_events_name == str)
        {
            std::cout << "\nERROR: [ MOUSE ]\n" << "The name given to this event already exist. \n\n";
            return;
        }
    }

    MOUSE_EVENTS.push_back(fnc);
    MOUSE_EVENTS_NAMES.push_back(str);
}

void EVENTS::List_Mouse_Event()
{
    std::cout << "\nMOUE-EVENTS:\n";
    for (auto &mouse_events_name : MOUSE_EVENTS_NAMES)
    {
        std::cout << " -- " << mouse_events_name << "\n";
    }
    std::cout << "\n";
}

void EVENTS::Delete_Mouse_Event(const char *str)
{
    bool not_found = true;

    for (size_t i = 0; i < MOUSE_EVENTS_NAMES.size(); i++)
    {
        if (MOUSE_EVENTS_NAMES[i] == str)
            {
                MOUSE_EVENTS_NAMES.erase(MOUSE_EVENTS_NAMES.begin() + i);
                MOUSE_EVENTS.erase(MOUSE_EVENTS.begin() + i);
                not_found = false;
            }
    }

    if (not_found == true)
        std::cout << "\nERROR: [ MOUSE ]\n" << "This events name does not exist. \n\n";
}
