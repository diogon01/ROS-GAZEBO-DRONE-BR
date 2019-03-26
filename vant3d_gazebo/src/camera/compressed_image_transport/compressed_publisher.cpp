//
// Created by vant3d on 25/03/19.
//

#include "compressed_publisher.h"
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/highgui/highgui.hpp>
#include <boost/make_shared.hpp>

#include "compression_common.h"

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

        switch (encodingFormat) {

            ///Caso JPEG
            case JPEG: {
                params[0] = CV_IMWRITE_JPEG_QUALITY;
                params[1] = config_.jpeg_quality;

                /// Update ros message format header
                compressed.format += "; jpeg compressed ";

                /// Check input format
                if ((bitDepth == 8) || (bitDepth == 16)) {
                    /// Target image format
                    std::string targetFormat;
                    if (enc::isColor(message.encoding)) {
                        /// convert color images to BGR8 format
                        targetFormat = "bgr8";
                        compressed.format += targetFormat;
                    }

                    /// OpenCV-ros bridge
                    try {
                        boost::shared_ptr<CompressedPublisher> tracked_object;
                        cv_bridge::CvImageConstPtr cv_ptr = cv_bridge::toCvShare(message, tracked_object, targetFormat);

                        /// Compress image
                        if (cv::imencode(".jpg", cv_ptr->image, compressed.data, params)) {

                            float cRatio = (float) (cv_ptr->image.rows * cv_ptr->image.cols * cv_ptr->image.elemSize())
                                           / (float) compressed.data.size();
                            ROS_DEBUG("Compressed Image Transport - Codec: jpg, Compression Ratio: 1:%.2f (%lu bytes)",
                                      cRatio, compressed.data.size());
                        } else {
                            ROS_ERROR("cv::imencode (jpeg) failed on input image");
                        }
                    }
                    catch (cv_bridge::Exception &e) {
                        ROS_ERROR("%s", e.what());
                    }
                    catch (cv::Exception &e) {
                        ROS_ERROR("%s", e.what());
                    }

                    /// Publish message
                    publish_fn(compressed);
                } else
                    ROS_ERROR(
                            "Compressed Image Transport - JPEG compression requires 8/16-bit color format (input format is: %s)",
                            message.encoding.c_str());

                break;
            }
                /// PNG Compression
            case PNG: {
                params[0] = CV_IMWRITE_PNG_COMPRESSION;
                params[1] = config_.png_level;

                /// Update ros message format header
                compressed.format += "; png compressed ";

                /// Check input format
                if ((bitDepth == 8) || (bitDepth == 16)) {

                    /// Target image format
                    stringstream targetFormat;
                    if (enc::isColor(message.encoding)) {
                        /// convert color images to RGB domain
                        targetFormat << "bgr" << bitDepth;
                        compressed.format += targetFormat.str();
                    }

                    /// OpenCV-ros bridge
                    try {
                        boost::shared_ptr<CompressedPublisher> tracked_object;
                        cv_bridge::CvImageConstPtr cv_ptr = cv_bridge::toCvShare(message, tracked_object,
                                                                                 targetFormat.str());

                        // Compress image
                        if (cv::imencode(".png", cv_ptr->image, compressed.data, params)) {

                            float cRatio = (float) (cv_ptr->image.rows * cv_ptr->image.cols * cv_ptr->image.elemSize())
                                           / (float) compressed.data.size();
                            ROS_DEBUG("Compressed Image Transport - Codec: png, Compression Ratio: 1:%.2f (%lu bytes)",
                                      cRatio, compressed.data.size());
                        } else {
                            ROS_ERROR("cv::imencode (png) failed on input image");
                        }
                    }
                    catch (cv_bridge::Exception &e) {
                        ROS_ERROR("%s", e.what());
                        return;
                    }
                    catch (cv::Exception &e) {
                        ROS_ERROR("%s", e.what());
                        return;
                    }

                    // Publish message
                    publish_fn(compressed);
                } else
                    ROS_ERROR(
                            "Compressed Image Transport - PNG compression requires 8/16-bit encoded color format (input format is: %s)",
                            message.encoding.c_str());
                break;
            }

            default:
                ROS_ERROR("Unknown compression type '%s', valid options are 'jpeg' and 'png'", config_.format.c_str());
                break;
        }

    }

}