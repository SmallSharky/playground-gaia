#include "zephyr/drivers/disk.h"
#include <lvgl.h>
// #include <lodepng/lv_lodepng.h>
#include <zephyr/drivers/display.h>
#include <zephyr/kernel.h>
// #include <device.h>
// #include <drivers/display.h>
#include <zephyr/fs/fs.h>

#include <zephyr/storage/disk_access.h>
#include <ff.h>



#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);


#include "widgets/hello_widget.hpp"

lv_obj_t *sd_status_icon = nullptr;

lv_obj_t *img = nullptr;

enum class StorageState
{
  MOUNTED,
  FAILED,
  ABSENT
};

enum class StorageStatus
{
  OK,
  UNMOUNTED,
  ABSENT
};

StorageState storageState = StorageState::ABSENT;

static void lv_example(void)
{
  lv_obj_t *label = lv_label_create(lv_scr_act());
  if (!label)
  {
    LOG_ERR("label is not created!");
    return;
  }
  lv_label_set_text(label, "Hello Zephyr LVGL!");
  lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);

  // SD Card Status Icon
  sd_status_icon = lv_label_create(lv_scr_act());
  if (!sd_status_icon)
  {
    LOG_ERR("SD status label is not created!");
    return;
  }
  lv_label_set_text(sd_status_icon, LV_SYMBOL_SD_CARD);
  lv_obj_set_style_text_color(sd_status_icon, lv_color_make(180, 180, 180), 0);
  lv_obj_align(sd_status_icon, LV_ALIGN_TOP_RIGHT, -5, 5);

  img = lv_image_create(lv_scr_act());
  /* Assuming a File system is attached to letter 'A'
   * E.g. set LV_USE_FS_STDIO 'A' in lv_conf.h */

  lv_obj_align(img, LV_ALIGN_BOTTOM_LEFT, 0, 0);


  HelloWidget * hw = HelloWidget::create(Widget::getActiveScreen());
  hw->doSomething();
}

static int lsdir(const char *path)
{
  int res;
  struct fs_dir_t dirp;
  static struct fs_dirent entry;
  int count = 0;

  fs_dir_t_init(&dirp);

  /* Verify fs_opendir() */
  res = fs_opendir(&dirp, path);
  if (res)
  {
    printk("Error opening dir %s [%d]\n", path, res);
    return res;
  }

  printk("\nListing dir %s ...\n", path);
  for (;;)
  {
    /* Verify fs_readdir() */
    res = fs_readdir(&dirp, &entry);

    /* entry.name[0] == 0 means end-of-dir */
    if (res || entry.name[0] == 0)
    {
      break;
    }

    if (entry.type == FS_DIR_ENTRY_DIR)
    {
      printk("[DIR ] %s\n", entry.name);
    }
    else
    {
      printk("[FILE] %s (size = %zu)\n",
             entry.name, entry.size);
    }
    count++;
  }

  /* Verify fs_closedir() */
  fs_closedir(&dirp);
  if (res == 0)
  {
    res = count;
  }

  return res;
}



/* Function to update SD card status using an icon */
void update_sd_status(StorageState s)
{
  if (s == StorageState::MOUNTED)
  {
    lv_obj_set_style_text_color(sd_status_icon, lv_color_make(0, 0, 0), 0);

    lsdir("/SD:/");

    // const char *fname = "/SD:/9485.PNG";
    const char *fname = "/SD:/AAAAAA.PNG";
    

    lv_image_set_src(img, fname);
  }
  else if (s == StorageState::ABSENT)
  {
    lv_obj_set_style_text_color(sd_status_icon, lv_color_make(100, 100, 100),
                                0);
  }
  else if (s == StorageState::FAILED)
  {
    lv_obj_set_style_text_color(sd_status_icon, lv_color_make(120, 0, 0), 0);
  }
}

FATFS fat_fs;
fs_mount_t fs_mnt;
volatile bool fs_mounted = false;

const char *disk_pdrv = "SD";

void init_disk(void)
{
  uint64_t memory_size_mb;
  uint32_t block_count;
  uint32_t block_size;

  if (disk_access_ioctl(disk_pdrv, DISK_IOCTL_CTRL_INIT, NULL) != 0)
  {
    LOG_ERR("Storage init ERROR!");
    return;
  }

  if (disk_access_ioctl(disk_pdrv, DISK_IOCTL_GET_SECTOR_COUNT, &block_count))
  {
    LOG_ERR("Unable to get sector count");
    return;
  }
  LOG_INF("Block count %u", block_count);

  if (disk_access_ioctl(disk_pdrv, DISK_IOCTL_GET_SECTOR_SIZE, &block_size))
  {
    LOG_ERR("Unable to get sector size");
    return;
  }
  LOG_INF("Sector size %u\n", block_size);

  memory_size_mb = (uint64_t)block_count * block_size;
  LOG_INF("Memory Size(MB) %u\n", (uint32_t)(memory_size_mb >> 20));

  if (disk_access_ioctl(disk_pdrv, DISK_IOCTL_CTRL_DEINIT, NULL) != 0)
  {
    LOG_ERR("Storage deinit ERROR!");
    return;
  }
}

int storage_mount(void)
{
  fs_mnt.type = FS_FATFS;
  fs_mnt.fs_data = &fat_fs;
  fs_mnt.mnt_point = "/SD:";
  int ret = fs_mount(&fs_mnt);
  if (ret == FR_OK)
  {
    LOG_INF("SD card mounted at /SD:");
  }
  else
  {
    LOG_ERR("SD card mount failed");
    return -1;
  }
  return 0;
}

void storage_unmount()
{
  fs_unmount(&fs_mnt);
}

void handle_storage_status(StorageStatus s)
{

  switch (s)
  {
  case StorageStatus::OK:
  {
    storageState = StorageState::MOUNTED;
    break;
  }
  case StorageStatus::UNMOUNTED:
  {
    if (storageState != StorageState::FAILED)
    {
      if (storage_mount())
      {
        // disk_access_ioctl(disk_pdrv, DISK_IOCTL_CTRL_INIT, NULL);
        // disk_access_ioctl(disk_pdrv, DISK_IOCTL_CTRL_DEINIT, NULL);
        if (disk_access_ioctl(disk_pdrv, DISK_IOCTL_CTRL_INIT, NULL))
        {
          storageState = StorageState::FAILED;
        }
        else
        {
          storageState = StorageState::ABSENT;
        }
      }
      else
      {
        storageState = StorageState::MOUNTED;
      }
    }
    break;
  }
  case StorageStatus::ABSENT:
  {
    if (storageState != StorageState::ABSENT)
    {
      storage_unmount();
      storageState = StorageState::ABSENT;
    }
    break;
  }
  }
}

void storage_status_timer(lv_timer_t *timer)
{
  int32_t status = disk_access_status("SD");
  auto stateBackup = storageState;
  switch (status)
  {
  case DISK_STATUS_UNINIT:
  {
    LOG_INF("UNI");
    handle_storage_status(StorageStatus::UNMOUNTED);
    break;
  }
  case DISK_STATUS_WR_PROTECT:
  case DISK_STATUS_NOMEDIA:
  {
    LOG_INF("ABS");
    handle_storage_status(StorageStatus::ABSENT);
    break;
  }
  case DISK_STATUS_OK:
  {
    handle_storage_status(StorageStatus::OK);
    break;
  }
  default:
  {
    LOG_WRN("Unknown disk status: %d", status);
    break;
  }
  }
  if (stateBackup != storageState)
  {
    update_sd_status(storageState);
  }
}

int main(void)
{
  const struct device *display_dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_display));
  if (!device_is_ready(display_dev))
  {
    LOG_ERR("Display not found!");
    return -1;
  }
  lv_init();

  lv_example();
  init_disk();
  //   storage_status_timer();
  display_blanking_off(display_dev);

  // lv_timer_t *timer = 
  lv_timer_create(storage_status_timer, 500, nullptr);

  // bool fsMountedPrev = false;
  while (1)
  {
    lv_task_handler();
    k_sleep(K_MSEC(10));
  }
}
