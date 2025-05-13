#pragma once

#include <QByteArray>

#include "include/Patcher.h"
#include "../../include/quest/Goods.h"

namespace PQH {
    class GoodsPatcher final: public Patcher {
    private:
        [[nodiscard]] QByteArray getPatchedHasDatasOffsets(const std::shared_ptr<Goods> &goodsData) const;
        [[nodiscard]] QByteArray getPatchedManageDataObjects(const std::shared_ptr<Goods> &goodsData) const;
        [[nodiscard]] QByteArray getPatchedHasDatas(const std::shared_ptr<Goods> &goodsData) const;
        [[nodiscard]] QByteArray getPatchedPlacementDatasOffsets(const std::shared_ptr<Goods> &goodsData) const;
        [[nodiscard]] QByteArray getPatchedPlacementDatasObjects(const std::shared_ptr<Goods> &goodsData) const;
        [[nodiscard]] QByteArray getPatchedPlacementDatas(const std::shared_ptr<Goods> &goodsData) const;
        [[nodiscard]] QByteArray getPatchedGoods(const std::shared_ptr<Goods> &goodsData) const;

    public:
        GoodsPatcher(const std::shared_ptr<uchar[]> &savedata, const int saveSize): Patcher(savedata, saveSize) {}

        [[nodiscard]] std::unique_ptr<uchar[]> patchGoods(const std::shared_ptr<Goods> &goodsData, int &newSaveSize) const;
    };
}
