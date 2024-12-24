#pragma once

#include "Item.h"

#include <vector>
#include <queue>
#include <set>
#include <optional>

struct State
{
    Item itemForNextState = Item::Unknown;
    std::optional<Item> itemToStayInState;
};

class SpringStateMachine
{
public:
    SpringStateMachine(std::vector<size_t> rules) {
        states.emplace_back(Item::Damaged, Item::Operative);
        for (const auto& rule : rules) {
            for (auto i = 0; i < rule - 1; ++i) {
                states.emplace_back(Item::Damaged);
            }
            states.emplace_back(Item::Operative);
            states.emplace_back(Item::Damaged, Item::Operative);
        }
        states.pop_back();
        states.pop_back();
    }

    std::optional<size_t> Transition(size_t fromState, Item item) {
        const auto state = states[fromState];
        if (state.itemForNextState == item) {
            return fromState + 1;
        }
        if (state.itemToStayInState && *state.itemToStayInState == item) {
            return fromState;
        }
        return {};
    }

    std::vector<Item> AcceptedItems(size_t fromState) {
        std::vector<Item> items;
        const auto state = states[fromState];
        items.push_back(state.itemForNextState);
        if (const auto itemToStayInState = state.itemToStayInState) {
            items.push_back(*itemToStayInState);
        }
        return items;
    }

    bool IsInFinalState(size_t state) {
        return state == states.size();
    }

private:
    std::vector<State> states;
};
