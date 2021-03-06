//------------------------------------------------------------------------------
/*
    This file is part of rippled: https://github.com/ripple/rippled
    Copyright (c) 2021 Ripple Labs Inc.

    Permission to use, copy, modify, and/or distribute this software for any
    purpose  with  or without fee is hereby granted, provided that the above
    copyright notice and this permission notice appear in all copies.

    THE  SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
    WITH  REGARD  TO  THIS  SOFTWARE  INCLUDING  ALL  IMPLIED  WARRANTIES  OF
    MERCHANTABILITY  AND  FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
    ANY  SPECIAL ,  DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
    WHATSOEVER  RESULTING  FROM  LOSS  OF USE, DATA OR PROFITS, WHETHER IN AN
    ACTION  OF  CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/
//==============================================================================

#ifndef RIPPLE_SIDECHAIN_IMPL_SIDECHAINLISTENER_H_INCLUDED
#define RIPPLE_SIDECHAIN_IMPL_SIDECHAINLISTENER_H_INCLUDED

#include <ripple/app/sidechain/impl/ChainListener.h>
#include <ripple/beast/utility/Journal.h>
#include <ripple/net/InfoSub.h>
#include <ripple/protocol/AccountID.h>

#include <memory>

namespace ripple {

class NetworkOPs;
class Application;

namespace sidechain {

class Federator;

class SidechainListener : public InfoSub,
                          public ChainListener,
                          public std::enable_shared_from_this<SidechainListener>
{
    Application& app_;

public:
    SidechainListener(
        Source& source,
        AccountID const& account,
        std::weak_ptr<Federator>&& federator,
        Application& app,
        beast::Journal j);

    void
    init(NetworkOPs& netOPs);

    ~SidechainListener() = default;

    void
    send(Json::Value const& msg, bool) override;

    void
    stopHistoricalTxns(NetworkOPs& netOPs);

    void
    send(
        std::string const& cmd,
        Json::Value const& params,
        RpcCallback onResponse) override;
};

}  // namespace sidechain
}  // namespace ripple

#endif
