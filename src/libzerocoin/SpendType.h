// Copyright (c) 2018 The PIVX developers
<<<<<<< Updated upstream
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef PIVX_SPENDTYPE_H
#define PIVX_SPENDTYPE_H
=======
// Copyright (c) 2018-2019 The PrimeStone developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef PrimeStone_SPENDTYPE_H
#define PrimeStone_SPENDTYPE_H
>>>>>>> Stashed changes

#include <cstdint>

namespace libzerocoin {
    enum SpendType : uint8_t {
<<<<<<< Updated upstream
        SPEND, // Used for a typical spend transaction, zPIV should be unusable after
        STAKE, // Used for a spend that occurs as a stake
        MN_COLLATERAL, // Used when proving ownership of zPIV that will be used for masternodes (future)
=======
        SPEND, // Used for a typical spend transaction, zPSC should be unusable after
        STAKE, // Used for a spend that occurs as a stake
        MN_COLLATERAL, // Used when proving ownership of zPSC that will be used for masternodes (future)
>>>>>>> Stashed changes
        SIGN_MESSAGE // Used to sign messages that do not belong above (future)
    };
}

<<<<<<< Updated upstream
#endif //PIVX_SPENDTYPE_H
=======
#endif //PrimeStone_SPENDTYPE_H
>>>>>>> Stashed changes
