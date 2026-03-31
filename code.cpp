#include <bits/stdc++.h>
using namespace std;

namespace DoubleLinkList {

struct NODE {
    int data{};
    NODE *next{nullptr};
    NODE *pre{nullptr};
    NODE() = default;
    explicit NODE(int val) : data(val), next(nullptr), pre(nullptr) {}
};

static NODE *head = nullptr; // sentinel head
static NODE *tail = nullptr; // sentinel tail
static int len = 0;

void Pre() {
    head = new NODE();
    tail = new NODE();
    head->pre = nullptr;
    tail->next = nullptr;
    head->next = tail;
    tail->pre = head;
    len = 0;
}

// Move to node at index i (0-based). If i == len, returns tail sentinel.
NODE *move(int i) {
    if (i <= 0) return head->next;      // i == 0
    if (i >= len) return tail;          // i == len
    // choose direction to minimize steps
    if (i <= len / 2) {
        NODE *cur = head->next; // index 0
        for (int j = 0; j < i; ++j) cur = cur->next;
        return cur;
    } else {
        NODE *cur = tail->pre; // index len-1
        for (int j = len - 1; j > i; --j) cur = cur->pre;
        return cur;
    }
}

void insert(int i, int x) {
    // Insert value x so that it occupies index i after insertion
    // Data guarantees 0 <= i <= len
    NODE *pos = move(i);     // node currently at index i (or tail if i==len)
    NODE *node = new NODE(x);
    NODE *prev = pos->pre;   // not null because pos is at least head->next
    node->next = pos;
    node->pre = prev;
    prev->next = node;
    pos->pre = node;
    ++len;
}

void remove(int i) {
    // Remove node at index i; guaranteed 0 <= i < len
    NODE *pos = move(i);
    NODE *prev = pos->pre;
    NODE *nxt = pos->next;
    prev->next = nxt;
    nxt->pre = prev;
    delete pos;
    --len;
}

int Get_length() { return len; }

int Query(int i) {
    if (i < 0 || i >= len) return -1;
    NODE *pos = move(i);
    return pos->data;
}

void Print() {
    if (len == 0) {
        cout << -1 << '\n';
        return;
    }
    NODE *cur = head->next;
    for (int i = 0; i < len; ++i) {
        if (i) cout << ' ';
        cout << cur->data;
        cur = cur->next;
    }
    cout << '\n';
}

void Clear() {
    // Delete all nodes including sentinels
    NODE *cur = head;
    while (cur != nullptr) {
        NODE *nxt = cur->next;
        delete cur;
        cur = nxt;
    }
    head = tail = nullptr;
    len = 0;
}

} // namespace DoubleLinkList

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;
    int op, x, p, ans;
    DoubleLinkList::Pre();
    for (int _ = 0; _ < n; ++_) {
        cin >> op;
        switch (op) {
        case 0:
            ans = DoubleLinkList::Get_length();
            cout << ans << '\n';
            break;
        case 1:
            cin >> p >> x;
            DoubleLinkList::insert(p, x);
            break;
        case 2:
            cin >> p;
            ans = DoubleLinkList::Query(p);
            cout << ans << '\n';
            break;
        case 3:
            cin >> p;
            DoubleLinkList::remove(p);
            break;
        case 4:
            DoubleLinkList::Print();
            break;
        default:
            // ignore unknown ops
            break;
        }
    }
    DoubleLinkList::Clear();
    return 0;
}
