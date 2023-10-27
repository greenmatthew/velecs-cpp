// vulkan_guide.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <vulkan/vulkan.h>

#include <vma/vk_mem_alloc.h>

#include <functional>
#include <deque>

struct DeletionQueue {
public:
    std::deque<std::function<void()>> deletors;

    void PushDeletor(std::function<void()>&& deletor)
    {
        deletors.push_back(std::move(deletor));
    }

    void Flush()
    {
        // reverse iterate the deletion queue to execute all the functions
        for (auto it = deletors.rbegin(); it != deletors.rend(); it++)
        {
            (*it)(); //call the function
        }

        deletors.clear();
    }
};

struct AllocatedBuffer
{
    VkBuffer _buffer{nullptr};
    VmaAllocation _allocation{nullptr};
};
