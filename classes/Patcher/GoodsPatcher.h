/*
 * This file is part of PQHex.
 * Copyright (C) 2025 kylon
 *
 * PQHex is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * PQHex is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
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
