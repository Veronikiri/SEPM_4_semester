bool init(subforwardlist **sfl) {
    *sfl = nullptr;
    return true;
}

bool push_back(subforwardlist **sfl, int d) {
    subforwardlist* new_node = new subforwardlist;
    if (!new_node) return false;
    new_node->data = d;
    new_node->next = nullptr;

    if (*sfl == nullptr) {
        *sfl = new_node;
        return true;
    }

    subforwardlist* current = *sfl;
    while (current->next) {
        current = current->next;
    }
    current->next = new_node;
    return true;
}

int pop_back(subforwardlist **sfl) {
    if (*sfl == nullptr) return 0;

    if ((*sfl)->next == nullptr) {
        int value = (*sfl)->data;
        delete *sfl;
        *sfl = nullptr;
        return value;
    }

    subforwardlist* current = *sfl;
    while (current->next->next) {
        current = current->next;
    }

    int value = current->next->data;
    delete current->next;
    current->next = nullptr;
    return value;
}

bool push_forward(subforwardlist **sfl, int d) {
    subforwardlist* new_node = new subforwardlist;
    if (!new_node) return false;
    new_node->data = d;
    new_node->next = *sfl;
    *sfl = new_node;
    return true;
}

int pop_forward(subforwardlist **sfl) {
    if (*sfl == nullptr) return 0;

    int value = (*sfl)->data;
    subforwardlist* temp = *sfl;
    *sfl = (*sfl)->next;
    delete temp;
    return value;
}

bool push_where(subforwardlist **sfl, unsigned int where, int d) {
    if (where == 0) return push_forward(sfl, d);

    subforwardlist* current = *sfl;
    for (unsigned int i = 0; i < where - 1 && current; i++) {
        current = current->next;
    }

    if (!current) return false;

    subforwardlist* new_node = new subforwardlist;
    if (!new_node) return false;
    new_node->data = d;
    new_node->next = current->next;
    current->next = new_node;
    return true;
}

int erase_where(subforwardlist **sfl, unsigned int where) {
    if (*sfl == nullptr) return 0;

    if (where == 0) return pop_forward(sfl);

    subforwardlist* current = *sfl;
    for (unsigned int i = 0; i < where - 1 && current; i++) {
        current = current->next;
    }

    if (!current || !current->next) return 0;

    subforwardlist* temp = current->next;
    int value = temp->data;
    current->next = temp->next;
    delete temp;
    return value;
}

unsigned int size(subforwardlist **sfl) {
    unsigned int count = 0;
    subforwardlist* current = *sfl;
    while (current) {
        count++;
        current = current->next;
    }
    return count;
}

void clear(subforwardlist **sfl) {
    while (*sfl) {
        subforwardlist* temp = *sfl;
        *sfl = (*sfl)->next;
        delete temp;
    }
}
