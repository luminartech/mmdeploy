// Copyright (c) OpenMMLab. All rights reserved.

/**
 * @file classifier.h
 * @brief Interface to MMClassification task
 */

#ifndef MMDEPLOY_CLASSIFIER_H
#define MMDEPLOY_CLASSIFIER_H

#include "common.h"
#include "executor.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct mm_class_t {
  int label_id;
  float score;
} mm_class_t;

/**
 * @brief Create classifier's handle
 * @param[in] model an instance of mmclassification sdk model created by
 * \ref mmdeploy_model_create_by_path or \ref mmdeploy_model_create in \ref model.h
 * @param[in] device_name name of device, such as "cpu", "cuda", etc.
 * @param[in] device_id id of device.
 * @param[out] handle instance of a classifier, which must be destroyed
 * by \ref mmdeploy_classifier_destroy
 * @return status of creating classifier's handle
 */
MMDEPLOY_API int mmdeploy_classifier_create(mm_model_t model, const char* device_name,
                                            int device_id, mm_handle_t* handle);

/**
 * @brief Create classifier's handle
 * @param[in] model_path path of mmclassification sdk model exported by mmdeploy model converter
 * @param[in] device_name name of device, such as "cpu", "cuda", etc.
 * @param[in] device_id id of device.
 * @param[out] handle instance of a classifier, which must be destroyed
 * by \ref mmdeploy_classifier_destroy
 * @return status of creating classifier's handle
 */
MMDEPLOY_API int mmdeploy_classifier_create_by_path(const char* model_path, const char* device_name,
                                                    int device_id, mm_handle_t* handle);

/**
 * @brief Use classifier created by  \ref mmdeploy_classifier_create_by_path to get label
 * information of each image in a batch
 * @param[in] handle classifier's handle created by  \ref mmdeploy_classifier_create_by_path
 * @param[in] mats a batch of images
 * @param[in] mat_count number of images in the batch
 * @param[out] results a linear buffer to save classification results of each
 * image, which must be freed by \ref mmdeploy_classifier_release_result
 * @param[out] result_count a linear buffer with length being \p mat_count to save the number of
 * classification results of each image. It must be released by \ref
 * mmdeploy_classifier_release_result
 * @return status of inference
 */
MMDEPLOY_API int mmdeploy_classifier_apply(mm_handle_t handle, const mm_mat_t* mats, int mat_count,
                                           mm_class_t** results, int** result_count);

/**
 * @brief Release the inference result buffer created \ref mmdeploy_classifier_apply
 * @param[in] results classification results buffer
 * @param[in] result_count \p results size buffer
 * @param[in] count length of \p result_count
 */
MMDEPLOY_API void mmdeploy_classifier_release_result(mm_class_t* results, const int* result_count,
                                                     int count);

/**
 * @brief Destroy classifier's handle
 * @param[in] handle classifier's handle created by \ref mmdeploy_classifier_create_by_path
 */
MMDEPLOY_API void mmdeploy_classifier_destroy(mm_handle_t handle);

/******************************************************************************
 * Experimental asynchronous APIs */

/**
 * @brief Same as \ref mmdeploy_classifier_create, but allows to control execution context of tasks
 * via exec_info
 */
MMDEPLOY_API int mmdeploy_classifier_create_v2(mm_model_t model, const char* device_name,
                                               int device_id, mmdeploy_exec_info_t exec_info,
                                               mm_handle_t* handle);

/**
 * @brief Pack classifier inputs into mmdeploy_value_t
 * @param[in] mats a batch of images
 * @param[in] mat_count number of images in the batch
 * @param[out] value the packed value
 * @return status of the operation
 */
MMDEPLOY_API int mmdeploy_classifier_create_input(const mm_mat_t* mats, int mat_count,
                                                  mmdeploy_value_t* value);

/**
 * @brief Same as \ref mmdeploy_classifier_apply, but input and output are packed in \ref
 * mmdeploy_value_t.
 */
MMDEPLOY_API int mmdeploy_classifier_apply_v2(mm_handle_t handle, mmdeploy_value_t input,
                                              mmdeploy_value_t* output);

/**
 * @brief Apply classifier asynchronously
 * @param[in] handle handle of the classifier
 * @param[in] input input sender that will be consumed by the operation
 * @param[out] output output sender
 * @return status of the operation
 */
MMDEPLOY_API int mmdeploy_classifier_apply_async(mm_handle_t handle, mmdeploy_sender_t input,
                                                 mmdeploy_sender_t* output);

/**
 *
 * @param[in] output output obtained by applying a classifier
 * @param[out] results a linear buffer containing classification results of each image, released by
 * \ref mmdeploy_classifier_release_result
 * @param[out] result_count a linear buffer containing the number of results for each input image,
 * released by \ref mmdeploy_classifier_release_result
 * @return status of the operation
 */
MMDEPLOY_API int mmdeploy_classifier_get_result(mmdeploy_value_t output, mm_class_t** results,
                                                int** result_count);

#ifdef __cplusplus
}
#endif

#endif  // MMDEPLOY_CLASSIFIER_H
