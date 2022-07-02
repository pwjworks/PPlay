//
// Created by pwjworks on 2022/7/1.
//

#include "IObserver.h"

void IObserver::AddObs(IObserver *obs) {
    if (!obs) return;
    std::lock_guard<std::mutex> lck(mux);
    obss.emplace_back(obs);
}

void IObserver::Notify(XData data) {
    std::lock_guard<std::mutex> lck(mux);
    for (auto &obs: obss) {
        obs->Update(data);
    }

}
