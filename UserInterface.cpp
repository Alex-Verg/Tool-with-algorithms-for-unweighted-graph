#include "UserInterface.h"

void UserInterface::fromFile(std::string path)
{
    std::ifstream f1;
    f1.exceptions(std::ifstream::badbit | std::ifstream::failbit);
    try
    {
        f1.open(path);    
    }
    catch (const std::exception&)
    {
        if (path == ".\\texts\\glossary.txt") std::cout << "������� ������ ��������� �� ���������." << std::endl;
        else if (path == ".\\texts\\manual.txt") std::cout << "������� ����������� ��������� �� ���������." << std::endl;
        else if (path == ".\\texts\\description.txt") std::cout << "���� �������� ��������� �� ���������." << std::endl;
        std::cout << " ��������� ��������� �� ����������." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        consoleClear();
        return;
    }
    std::string str;
    while (!f1.eof()) {
        std::getline(f1, str); 
        std::cout << str << std::endl;
    }
    std::cin >> str;
    consoleClear();
}

void UserInterface::graphMenu()
{
    std::ifstream f1;
    f1.exceptions(std::ifstream::badbit | std::ifstream::failbit);
    try
    {
        f1.open(".\\texts\\graphMenu.txt");
    }
    catch (const std::exception&) {
        std::cout << " ����� ������ � ������ ���������.\n" << "��������� ��������� �� ����������." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        consoleClear();
        return;
    }
    
    int item = 0;
    Graph cur_graph;

    while (item != 14) {
        std::string str;
        if (!m_isGraph) {
            for (int i = 0; i < 3; i++) {
                std::getline(f1, str);
                std::cout << str << std::endl;                
            }
            std::cout << " 2. ��������� ������ � ������." << std::endl;
        }
        else {
            while (!f1.eof()) {
                std::getline(f1, str);
                std::cout << str << std::endl;
            }
        }
        f1.clear();
        f1.seekg(0);

        std::cin >> item;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
        }        
        if (!m_isGraph) {
            if (item == 1) {
                consoleClear(); 
                inputEdgeList(cur_graph);
            }
            else if (item == 2) {
                consoleClear();
                m_isGraph = false;
                break;
            }
            else {
                std::cout << "������� ����������� �����. �������� ������ ��������." << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                consoleClear();
            }
        }
        else {
            switch (item)
            {
            case 1: {consoleClear(); inputEdgeList(cur_graph); break; }                                         //+
            case 2: {consoleClear(); graphEdge(cur_graph, true); break; }                                       //+
            case 3: {consoleClear(); addGraphVertex(cur_graph); break; }                                        //+
            case 4: {consoleClear(); graphEdge(cur_graph, false); break; }                                      //+
            case 5: {consoleClear(); deleteGraphVertex(cur_graph); break; }                                     //+
            case 6: {consoleClear(); printGraph(cur_graph); break; }                                            //+
            case 7: {consoleClear(); FS(cur_graph, false); break; }                                             //+
            case 8: {consoleClear(); FS(cur_graph, true); break; }                                              //+
            case 9: {consoleClear(); graphComponents(cur_graph); break; }                                       //+
            case 10: {consoleClear(); graphCutPoints(cur_graph); break; }                                       //+
            case 11: {consoleClear(); graphBridges(cur_graph); break; }                                         //
            case 12: {consoleClear(); isGraphBipartite(cur_graph); break; }                                     //+
            case 13: {consoleClear(); graphTopSort(cur_graph); break; }                                         //+
            case 14: {consoleClear(); m_isGraph = false;  break; }
            default: {
                std::cout << "������� ����������� �����. �������� ������ ��������." << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                consoleClear();
            }
            }
        }
    }

    std::cout << "������ � ������ ������ ���������!" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    consoleClear();
}

void UserInterface::inputEdgeList(Graph& gr)
{   
    int count_ver = 0, count_edg = 0, orient, i, v1, v2, error_edg = 0;
    std::vector <std::pair < int, int>> list;
       

    std::cout << "�������� ����� � ������ ������ �����." << std::endl <<
        "���� ���� ���������� ������ 1, ���� � - ������ 0." << std::endl;
    while (true) {
        std::cin >> orient;
        if (std::cin.fail() || (orient > 1 || orient < 0)) {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            std::cout << "������ �������� ��������!" << std::endl;
            orient = 0;
        }
        else {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            break;
        }
    }

    std::cout << "������ ������� ������ � �����:" << std::endl;
    while (true) {
        std::cin >> count_ver;
        if (std::cin.fail() || count_ver <= 0)
        {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            std::cout << "������ �������� ��������!" << std::endl;
        }
        else { 
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            break; 
        }
    }
    long max_e = count_ver * (count_ver - 1) * (orient + 1) / 2;
    std::cout << "������ ������� ����� � �����:" << std::endl;
    while (true) {
        std::cin >> count_edg;
        if (std::cin.fail() || count_edg < 0 || count_edg > max_e)
        {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            std::cout << "������ �������� ��������!" << std::endl;
        }
        else break;
    }

    std::cout << "� ��������� ������ ������ ����� ����� " << std::endl << 
        "(�� ������ � �����), ������� �� ������� �������," << std::endl <<
        "� ��� �������� �����, �� �������, � ��� �������." << std::endl <<
        "������� ������������ ��������� � 1!" << std::endl <<
        "���������� ������ ����� ���������� �� ������!" << std::endl
        << "������� ����� ������ ������ ����� �����." << std::endl;
    for (i = 0; i < count_edg; i++) {
        std::cin >> v1 >> v2;
        if (std::cin.fail() || (v1 <= 0 || v1 > count_ver) || (v2 <= 0 || v2 > count_ver) || (v1 == v2)) {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            std::cout << "������� ���������� �����, ���� �� ���� ������." << std::endl;
            error_edg++;
        }
        else {
            list.push_back(std::make_pair(v1, v2));
        }
    }

    count_edg -= error_edg;
    gr.inputGraph(count_ver, count_edg, list, orient);

    m_isGraph = true;

    std::cout << "���� ������ ������ ������� �����!" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    consoleClear();
}

void UserInterface::graphEdge(Graph& gr, bool add)
{
    int v1, v2;
    std::cout << "� ���������� ����� ������ �� �������," << std::endl <<
        "� ��� �������� �� � ��� ������� �����," << std::endl;
    if (add) std::cout << "�� ��������� ������ � ����." << std::endl;
    else std::cout << "�� ��������� �������� � �����." << std::endl;
    while (true) {
        std::cin >> v1 >> v2;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            std::cout << "������� ��������� ���, �������� ������" << std::endl;
        }
        else {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            break;
        }
    }
    if (add) {
        if (gr.addEdge(std::make_pair(v1, v2))) std::cout <<
            "����� ������ ������ � ����!" << std::endl;
        else std::cout << "����� �� ������� ������ � ����." << std::endl;
    }
    else {
        if (gr.deleteEdge(std::make_pair(v1, v2))) std::cout <<
            "����� ������ �������� � �����!" << std::endl;
        else std::cout << "����� �� ������� �������� � �����." << std::endl;
    }
    std::this_thread::sleep_for(std::chrono::seconds(2));
    consoleClear();
}

void UserInterface::addGraphVertex(Graph& gr)
{
    int new_ver = gr.addVertex();
    std::cout << "� ���� ������ ������ �������!" << std::endl <<
        "���� ������� �� ���������� ����� " << new_ver << std::endl <<
        "(��������� ���������� � 1)." << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(2));
    consoleClear();
}

void UserInterface::deleteGraphVertex(Graph& gr)
{
    int v;
    std::cout << "� ���������� ����� ������ ����� �������," << std::endl <<
        "��� ��������� �������� � �����." << std::endl;

    while (true) {
        std::cin >> v;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            std::cout << "������� ��������� ���, �������� ������" << std::endl;
        }
        else break;
    }

    if (gr.deleteVertex(v)) std::cout <<
        "������� ������ �������� � �����!" << std::endl;
    else std::cout << "������� �� ������� �������� � �����." << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(2));
    consoleClear();
    return;
}

void UserInterface::printGraph(Graph& gr)
{
    gr.print();
    wait();
}

void UserInterface::FS(Graph& gr, bool BFS)
{
    std::cout << "������ �������, � ��� ������ ����� ";
    if (BFS) std::cout << "� ������:" << std::endl;
    else std::cout << "� �������." << std::endl;
    std::cout << "���� ������� �� ���������, ����� ���������" << std::endl <<
        "� ����� �������� �������." << std::endl;

    int start_v;
    while (true) {
        std::cin >> start_v;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            std::cout << "������� ��������� ���, �������� ������" << std::endl;
        }
        else {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            break;
        }
    }

    if (BFS) gr.BFS(start_v);
    else gr.DFS(start_v);

    wait();
}

void UserInterface::graphComponents(Graph& gr)
{
    std::vector <std::set<int>> components = gr.componentsSearch();
    int count_comp = components.size(), i;
    std::cout << "� ����� " << count_comp;
    if (count_comp > 10 && count_comp < 20) std::cout << " ���������";
    else {
        switch (count_comp % 10)
        {
        case 1: {std::cout << " ����������"; break; }
        case 2: {std::cout << " ����������"; break; }
        case 3: {std::cout << " ����������"; break; }
        case 4: {std::cout << " ����������"; break; }
        default: {std::cout << " ���������"; break; }
        }
    }
    if (gr.isOrient()) std::cout << " ������";
    std::cout << " ��'������." << std::endl;

    for (i = 0; i < count_comp; i++) {
        std::cout << "������� " << i + 1 << "-� ����������";
        if (gr.isOrient()) std::cout << " ������";
        std::cout << " ��'������." << std::endl;
        for (auto j : components[i]) {
            std::cout << j << " ";
        }
        std::cout << std::endl;
    }

    wait();
}

void UserInterface::graphCutPoints(Graph& gr)
{
    if (gr.isOrient()) {
        std::cout << "�������� ����� �'������� ����������" << std::endl << "��� ����������� �����!" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        consoleClear();
        return;
    }

    std::set<int> cutPoints = gr.cutpointsSearch();

    std::cout << "� ����� " << cutPoints.size();
    
    if (cutPoints.size() > 10 && cutPoints.size() < 20) std::cout << " �����";
    else {
        switch (cutPoints.size() % 10)
        {
        case 1: {std::cout << " �����"; break; }
        case 2: {std::cout << " �����"; break; }
        case 3: {std::cout << " �����"; break; }
        case 4: {std::cout << " �����"; break; }
        default: {std::cout << " �����";
            break; 
        }
        }
    }

    std::cout << " �'�������" << std::endl << "(�� ��������� �������� �� ���������" << std::endl << 
        "������� ��������� ��'������):" << std::endl;

    for (auto i : cutPoints) {
        std::cout << i << " ";
    }

    wait();
}

void UserInterface::graphBridges(Graph& gr)
{
    if (gr.isOrient()) {
        std::cout << "�������� ����� ����������" << std::endl << "��� ����������� �����!" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        consoleClear();
        return;
    }

    std::set<std::pair<int, int>> bridges = gr.bridgesSearch();

    std::cout << "� ����� " << bridges.size();

    if (bridges.size() > 10 && bridges.size() < 20) std::cout << " �����";
    else {
        switch (bridges.size() % 10)
        {
        case 1: {std::cout << " ���"; break; }
        case 2: {std::cout << " �����"; break; }
        case 3: {std::cout << " �����"; break; }
        case 4: {std::cout << " �����"; break; }
        default: { std::cout << " �����";
            break; 
        }
        }
    }

    std::cout << std::endl << "(�� ��������� �������� �� ���������" << std::endl <<
        "������� ��������� ��'������):" << std::endl;

    for (auto i : bridges) {
        std::cout << i.first << " " << i.second << std::endl;
    }

    wait();
}

void UserInterface::isGraphBipartite(Graph& gr)
{
    std::vector <std::set<int>> parts = gr.isBepartite();

    if (parts.empty()) std::cout << "���� �� � ����������!" << std::endl;
    else {
        std::cout << "���� ����������." << std::endl;
        for (int i = 1; i < 3; i++) {
            std::cout << "�������� ������� " << i << "-� ���:" << std::endl;
            for (auto j : parts[i - 1]) {
                std::cout << j << " ";
            }
            std::cout << std::endl;
        }
    }

    wait();
}

void UserInterface::graphTopSort(Graph& gr)
{
    std::vector <int> sort_order = gr.topologicalSort();
    int size = sort_order.size();

    if (sort_order.empty()) {
        std::cout << "���������� ���������� ����� �� �������!" << std::endl <<
            "���� �� � ���������� ��������� ������!" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        consoleClear();
        return;
    }
    else {
        std::cout << "���������� ���������� ������ ��������!" << std::endl;
        std::cout << "������� ���������� ������������ ������:" << std::endl;
        for (int i = size - 1; i >= 0; i--) {
            std::cout << sort_order[i] << " ";
        }
    }

    wait();
}

void UserInterface::consoleClear()
{
    #ifdef _WIN32 || _WIN64
    COORD topLeft = { 0, 0 };
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen;
    DWORD written;

    GetConsoleScreenBufferInfo(console, &screen);
    FillConsoleOutputCharacterA(
        console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
    );
    FillConsoleOutputAttribute(
        console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
        screen.dwSize.X * screen.dwSize.Y, topLeft, &written
    );
    SetConsoleCursorPosition(console, topLeft);
	#else
		#include <unistd.h>

        std::cout << "\x1B[2J\x1B[H";
	#endif
}

void UserInterface::wait()
{
    std::string str;
    std::cout << std::endl << std::endl << "(��� ����������� �� ���� ������ ����-���� ������)" << std::endl;
    std::cin >> str;
    consoleClear();
}

void UserInterface::mainMenu()
{   
    int item = 0;
    while (item != 5) {
        std::cout << "\t��� ��� �������� ��� ������ � ����������� � �������������" << std::endl <<
            "\t\t����������� �������� �������!" << std::endl <<
            "\t� ������� ��������������� ���������� ���������� ���� ������." << std::endl <<
            "\t\t��������� ����� ����������� � �������� ������." << std::endl <<
            "\t����� ������ ������������ �������� ������ ��������� ������� �����������.\n\n" << std::endl;
        std::cout << "\t\t\t\t������� ����" << std::endl;
        std::cout << "\t\t(��� ��������� ����������� ������ ������ ���� �����)" << std::endl;
        std::cout << "1. ������ ������ � ������." << std::endl;
        std::cout << "2. ������� ������." << std::endl;
        std::cout << "3. ������� �����������." << std::endl;
        std::cout << "4. ��� ��������." << std::endl;
        std::cout << "5. ��������� ������." << std::endl;
        
        std::cin >> item;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
        }
        
        switch (item)
        {
        case 1: {consoleClear(); graphMenu(); break; }
        case 2: {consoleClear(); fromFile(".\\texts\\glossary.txt"); break; }
        case 3: {consoleClear(); fromFile(".\\texts\\manual.txt"); break; }
        case 4: {consoleClear(); fromFile(".\\texts\\description.txt"); break; }
        case 5: {consoleClear(); break; }
        default: {
            std::cout << "������� ����������� �����. �������� ������ ��������." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(2));
            consoleClear();
        }
        }
    }

    std::cout << "������ �������� ������ ���������!" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

UserInterface::UserInterface()
{
    this->m_isGraph = false;
}