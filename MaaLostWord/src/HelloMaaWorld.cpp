#include <MaaLostWord/HelloMaaWorld.h>

namespace MaaLostWord
{
    MaaController* create_adb_controller();
    struct HelloMaaWorldImpl
    {

        void Run()
        {
            std::string user_path = "./";
            MaaToolkitConfigInitOption(user_path.c_str(), "{}");

            auto controller_handle = create_adb_controller();
            // auto controller_handle = create_win32_controller();
            auto ctrl_id = MaaControllerPostConnection(controller_handle);

            // TODO: wait for controller to be ready
            // MaaControllerWait(controller_handle, ctrl_id);
        }
    };

    void HelloMaaWorld()
    {
        HelloMaaWorldImpl impl;
        impl.Run();
    }


/**
 * Creates an ADB controller for the first available ADB device or a user-selected device
 * if multiple are available.
 *
 * This function initializes the ADB device list, prompts the user to select a device
 * if multiple devices are found, and uses the selected device to create an ADB controller.
 * It returns a pointer to the created MaaController or nullptr if no devices are found.
 *
 * @return MaaController* Pointer to the created ADB controller, or nullptr if no device is available.
 */
    MaaController* create_adb_controller()
    {
        auto list_handle = MaaToolkitAdbDeviceListCreate();
        auto destroy = [&]() {
            MaaToolkitAdbDeviceListDestroy(list_handle);
        };

        MaaToolkitAdbDeviceFind(list_handle);

        size_t size = MaaToolkitAdbDeviceListSize(list_handle);
        if (size == 0) {
            std::cout << "No device found" << std::endl;

            destroy();
            return nullptr;
        }

        size_t device_index = 0;
        if (size > 1) {
            std::cout << "Multiple devices found. Please choose one:" << std::endl;
            for (size_t i = 0; i < size; ++i) {
                auto device_handle = MaaToolkitAdbDeviceListAt(list_handle, i);
                std::string device_name = MaaToolkitAdbDeviceGetName(device_handle);
                std::string device_address = MaaToolkitAdbDeviceGetAddress(device_handle);
                std::cout << i << ": " << device_name << " (" << device_address << ")" << std::endl;
            }

            std::cout << "Input device index: ";
            std::cin >> device_index;
        }

        auto device_handle = MaaToolkitAdbDeviceListAt(list_handle, device_index);

        std::string agent_path = "share/MaaAgentBinary";
        auto controller_handle = MaaAdbControllerCreate(
            MaaToolkitAdbDeviceGetAdbPath(device_handle),
            MaaToolkitAdbDeviceGetAddress(device_handle),
            MaaToolkitAdbDeviceGetScreencapMethods(device_handle),
            MaaToolkitAdbDeviceGetInputMethods(device_handle),
            MaaToolkitAdbDeviceGetConfig(device_handle),
            agent_path.c_str(),
            nullptr,
            nullptr);

        destroy();

        return controller_handle;
    }
}