#pragma once
#include <mc/src-deps/core/utility/pubsub/detail/DispatchingPublisherBase.hpp>
#include <mc/src-deps/core/utility/pubsub/detail/SubscriptionBody.hpp>
#include <mc/src-deps/core/utility/pubsub/Conector.hpp>

namespace Bedrock::PubSub {
    template <typename Signature, typename ThreadingModel>
    class Publisher  : 
        public Bedrock::PubSub::Detail::DispatchingPublisherBase<ThreadingModel, Bedrock::PubSub::Detail::SubscriptionBody<Signature>>,
        public Bedrock::PubSub::Connector<Signature> 
    {
    public:
        typedef std::function<Signature> FunctionType;
        virtual ~Publisher();

    /* private: */
        virtual Bedrock::PubSub::Subscription _connectInternal(
            FunctionType&&, 
            Bedrock::PubSub::ConnectPosition, 
            std::unique_ptr<Bedrock::PubSub::SubscriptionContext>&&, 
            std::optional<int>
        );
    };
}