template<typename T>
class subforwardlist {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& val) : data(val), next(nullptr) {}
    };

    Node* head;

public:
    subforwardlist() : head(nullptr) {}

    ~subforwardlist() {
        clear();
    }

    subforwardlist(const subforwardlist& other) : head(nullptr) {
        if (!other.head) return;

        head = new Node(other.head->data);
        Node* current = head;
        Node* other_current = other.head->next;

        while (other_current) {
            current->next = new Node(other_current->data);
            current = current->next;
            other_current = other_current->next;
        }
    }

    subforwardlist(subforwardlist&& other) : head(other.head) {
        other.head = nullptr;
    }

    subforwardlist& operator=(const subforwardlist& other) {
        if (this == &other) return *this;

        clear();
        if (!other.head) return *this;

        head = new Node(other.head->data);
        Node* current = head;
        Node* other_current = other.head->next;

        while (other_current) {
            current->next = new Node(other_current->data);
            current = current->next;
            other_current = other_current->next;
        }

        return *this;
    }

    subforwardlist& operator=(subforwardlist&& other) {
        if (this != &other) {std::swap(head, other.head);}
        return *this;
    }

    void push_back(const T& data) {
        Node* new_node = new Node(data);
        if (!head) {
            head = new_node;
            return;
        }
        Node* current = head;
        while (current->next) {current = current->next;}
        current->next = new_node;
    }

    T pop_back() {
        if (!head) return T{};
        if (!head->next) {
            T data = head->data;
            delete head;
            head = nullptr;
            return data;
        }
        Node* current = head;
        while (current->next->next) {current = current->next;}
        T data = current->next->data;
        delete current->next;
        current->next = nullptr;
        return data;
    }

    void push_forward(const T& data) {
        Node* new_node = new Node(data);
        new_node->next = head;
        head = new_node;
    }

    T pop_forward() {
        if (!head) return T{};
        T data = head->data;
        Node* temp = head;
        head = head->next;
        delete temp;
        return data;
    }

    void push_where(unsigned int where, const T& data) {
        if (where == 0) {
            push_forward(data);
            return;
        }

        Node* current = head;
        for (unsigned int i = 1; i < where && current; ++i) {current = current->next;}
        if (!current) return;

        Node* new_node = new Node(data);
        new_node->next = current->next;
        current->next = new_node;
    }

    T erase_where(unsigned int where) {
        if (where == 0) {return pop_forward();}

        Node* current = head;
        for (unsigned int i = 1; i < where && current; ++i) {current = current->next;}
        if (!current || !current->next) return T{};

        Node* temp = current->next;
        T data = temp->data;
        current->next = temp->next;
        delete temp;
        return data;
    }

    unsigned int size() const {
        unsigned int count = 0;
        Node* current = head;
        while (current) {
            ++count;
            current = current->next;
        }
        return count;
    }

    void clear() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};
