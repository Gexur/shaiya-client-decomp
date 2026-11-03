#include "system_messages.h"
#include "runtime/allocations.h"
#include "runtime/string_errors.h"
#include "core/owner112.h"
namespace {
using String = shaiya::startup::String_00405710;
struct LimitText {
    String s;
    LimitText(const char* t, uint32_t n) {
        s.capacity_018 = 15;
        s.size_014 = 0;
        s.storage_004[0] = 0;
        FUN_00405710(&s, t, n);
    }
    ~LimitText() {
        FUN_00529db0(&s);
    }
};
[[noreturn]] void too_long(const char* t, uint32_t n) {
    LimitText message(t, n);
    OriginalLogicError error;
    FUN_0040ad80(&error, &message.s);
    error.base.vtable = &dat_006dbc80;
    fun_005cce46(&error, const_cast<CxxThrowInfo*>(&dat_006fa52c));
    __builtin_unreachable();
}
void clear_list(OriginalMessageList* l) {
    shaiya::ui::FUN_004ce800(reinterpret_cast<OriginalOwner112Fields*>(l));
}
void release_list(OriginalMessageList* l) {
    shaiya::ui::FUN_00447020(reinterpret_cast<OriginalOwner112Fields*>(l));
}
struct ListsUnwind {
    OriginalMessageOwner* p;
    uint32_t count = 0;
    bool active = true;
    ~ListsUnwind() noexcept(false) {
        if (active)
            while (count)
                release_list(&p->lists[--count]);
    }
};
OriginalMessageNode* new_header() {
    auto* p = static_cast<OriginalMessageNode*>(fun_005cc96d(12));
    uint32_t a = reinterpret_cast<uint32_t>(p);
    if (a)
        *reinterpret_cast<volatile uint32_t*>(a) = a;
    if (a + 4)
        *reinterpret_cast<volatile uint32_t*>(a + 4) = a;
    return p;
}
OriginalTreeNode24* insert(OriginalTree12* t, OriginalTreeNode24* parent, bool left, int32_t key) {
    if (t->count > 0x1ffffffd)
        too_long("map/set<T> too long", 19);
    auto* n = static_cast<OriginalTreeNode24*>(fun_005cc96d(24));
    if (n) {
        n->left = t->header;
        n->right = t->header;
        n->parent = parent;
        n->payload0c = uint32_t(key);
        n->payload10 = 0;
        n->color = 0;
        n->is_header = 0;
    }
    ++t->count;
    if (parent == t->header) {
        t->header->parent = n;
        t->header->left = n;
        t->header->right = n;
    } else if (left) {
        parent->left = n;
        if (parent == t->header->left)
            t->header->left = n;
    } else {
        parent->right = n;
        if (parent == t->header->right)
            t->header->right = n;
    }
    auto* x = n;
    while (x->parent->color == 0) {
        auto* p = x->parent;
        auto* g = p->parent;
        if (p == g->left) {
            auto* u = g->right;
            if (!u->color) {
                p->color = 1;
                u->color = 1;
                g->color = 0;
                x = g;
            } else {
                if (x == p->right) {
                    FUN_00421720(t, p);
                    x = p;
                }
                x->parent->color = 1;
                x->parent->parent->color = 0;
                FUN_00444130(t, x->parent->parent);
            }
        } else {
            auto* u = g->left;
            if (!u->color) {
                p->color = 1;
                u->color = 1;
                g->color = 0;
                x = g;
            } else {
                if (x == p->left) {
                    FUN_00444130(t, p);
                    x = p;
                }
                x->parent->color = 1;
                x->parent->parent->color = 0;
                FUN_00421720(t, x->parent->parent);
            }
        }
    }
    t->header->parent->color = 1;
    return n;
}
} // namespace
extern "C" uint32_t* __attribute__((thiscall)) FUN_0041f230(OriginalTree12* t, const int32_t* key) {
    auto* hint = t->header;
    auto* n = hint->parent;
    while (!n->is_header) {
        if (int32_t(n->payload0c) < *key)
            n = n->right;
        else {
            hint = n;
            n = n->left;
        }
    }
    if (hint != t->header && int32_t(hint->payload0c) <= *key)
        return &hint->payload10;
    if (!t->count)
        n = insert(t, t->header, true, *key);
    else if (hint == t->header)
        n = insert(t, t->header->right, false, *key);
    else if (hint == t->header->left)
        n = insert(t, hint, true, *key);
    else {
        auto* previous = hint;
        if (!previous->left->is_header) {
            previous = previous->left;
            while (!previous->right->is_header)
                previous = previous->right;
        } else {
            auto* p = previous->parent;
            while (!p->is_header && previous == p->left) {
                previous = p;
                p = p->parent;
            }
            previous = p;
        }
        n = previous->right->is_header ? insert(t, previous, false, *key)
                                       : insert(t, hint, true, *key);
    }
    return &n->payload10;
}
extern "C" OriginalMessageOwner* __attribute__((thiscall))
FUN_0041f570(OriginalMessageOwner* self) {
    ListsUnwind unwind{self};
    for (auto& list : self->lists) {
        list.header = new_header();
        list.count = 0;
        ++unwind.count;
    }
    FUN_0041f2e0();
    for (uint32_t& v : self->enabled)
        v = 1;
    for (auto& list : self->lists) {
        clear_list(&list);
        for (uint32_t i = 0; i < 100; ++i) {
            auto* payload = static_cast<uint32_t*>(fun_005cc96d(0x10c));
            if (payload) {
                for (uint32_t j = 0; j < 0x41; ++j)
                    payload[j] = 0;
                auto* head = list.header;
                auto* n = static_cast<OriginalMessageNode*>(fun_005cc96d(12));
                if (n) {
                    n->next = head;
                    n->previous = head->previous;
                    n->payload = payload;
                }
                if (0x3fffffffu - list.count < 1)
                    too_long("list<T> too long", 16);
                ++list.count;
                head->previous = n;
                n->previous->next = n;
            }
        }
    }
    self->value1c = 0;
    self->value18 = 0;
    self->value40 = 0;
    self->value44 = 0;
    self->value48 = 0;
    unwind.active = false;
    return self;
}
extern "C" void __attribute__((thiscall)) FUN_0041e420(OriginalMessageOwner* self) {
    ListsUnwind unwind{self, 2};
    FUN_0041e1b0();
    for (auto& list : self->lists) {
        for (auto* n = list.header->next; n != list.header; n = n->next)
            fun_005cc620(n->payload);
        clear_list(&list);
    }
    unwind.active = false;
    release_list(&self->lists[1]);
    release_list(&self->lists[0]);
}
