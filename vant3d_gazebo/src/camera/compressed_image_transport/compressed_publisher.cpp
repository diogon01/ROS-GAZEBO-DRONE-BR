//
// Created by vant3d on 25/03/19.
//

#include "compressed_image_transport/compressed_publisher.h"
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/highgui/highgui.hpp>
#include <boost/make_shared.hpp>

#include "compressed_image_transport/compression_common.h"

#include <vector>
#include <sstream>

using namespace cv;
using namespace std;

namespace enc = sensor_msgs::image_encodings;

namespace compressed_image_transport {

    void CompressedPublisher::advertiseImpl(ros::NodeHandle &nh, const std::string &base_topic, uint32_t queue_size,
                                            const image_transport::SubscriberStatusCallback &user_connect_cb,
                                            const image_transport::SubscriberStatusCallback &user_disconnect_cb,
                                            const ros::VoidPtr &tracked_object, bool latch) {

        typedef image_transport::SimplePublisherPlugin<sensor_msgs::CompressedImage> Base;
        Base::advertiseImpl(nh, base_topic, queue_size, user_connect_cb, user_disconnect_cb, tracked_object, latch);

        /// Set a reconfiguração de server para este topico
        reconfigure_server_ = boost::make_shared<ReconfigureServer>(this->nh());
        ReconfigureServer::CallbackType f = boost::bind(&CompressedPublisher::configCb, this, _1, _2);
        reconfigure_server_->setCallback(f);
    }

    void CompressedPublisher::configCb(compressed_image_transport::CompressedPublisher::Config &config,
                                       uint32_t level) {
        config_ = config;

    }

    void CompressedPublisher::publish(const sensor_msgs::Image &message,
                                      const image_transport::SimplePublisherPlugin<sensor_msgs::CompressedImage_<std::allocator<void>>>::PublishFn &publish_fn) const {

        /// Comprimindo imagen na mensagem
        sensor_msgs::CompressedImage compressed;
        compressed.header = message.header;
        compressed.format = message.encoding;

        /// Comprimindo configurações
        std::vector<int> params;
        params.resize(3, 0);

        /// Pega Configuração de codigo
        compressionFormat encodingFormat = UNDEFINED;
        if (config_.format == compressed_image_transport::CompressedPublisher_jpeg) {
            encodingFormat = JPEG;
        }
        if (config_.format == compressed_image_transport::CompressedPublisher_png) {
            encodingFormat = PNG;
        }

        /// Bit depth of image encondig
        int bitDepth = enc::bitDepth(message.encoding);
        int numChannels = enc::numChannels(message.encoding);
    }


}